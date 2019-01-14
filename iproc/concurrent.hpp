/****************************************************************************
**
** Copyright (C) 2016 sergeiudris
** Contact: sergei.udris@gmail.com
**
** This file is part of Linux Memory Monitor
** Program uses /proc interface to calculate precise RAM usage for a group of processes,
** e.g. browser,database etc., excluding shared and not present(swapped out) memory pages
**
**
** Linux Memory Monitor is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** Linux Memory Monitor is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with Linux Memory Monitor.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#ifndef CONCURRENT
#define CONCURRENT


#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <unordered_map>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>

namespace iproc{

template <class Collection>
class Container {
protected:
    std::mutex mutexCollection_;
    std::mutex mutexThreads_;
    std::condition_variable cv_;
    std::deque<std::thread> threads_;
public:
    Collection collection_;

    Container(Collection& c){
        collection_ = std::move(c);
    }

    Container(){}
    virtual ~Container(){
        for(auto& t: threads_){
            t.join();
        }
    }
    Container(const Container&& other){
        this->collection_ = std::move(other.collection_);
    }
    Container(const Container& other){
        this->collection_ = std::move(other.collection_);
    }
    Container& operator=(Container&& other){
        this->collection_ = std::move(other.collection_);
    }
    Container& operator=(const Container& other){
        this->collection_ = std::move(other.collection_);
    }

    template <class Func>
    void forEachAsync(Func processor){
        std::lock_guard<std::mutex> lock(mutexThreads_);
        for(auto& el: collection_){
            threads_.push_back(std::thread(processor,std::ref(el)));
        }
        for(auto& t: threads_){
            t.join();
            threads_.pop_front();
        }
    }

    auto begin(){
        return collection_.begin();
    }
    auto end(){
        return collection_.end();
    }
};

template <class Elem>
class concurrent_vector: public Container<std::vector<Elem>>
{
public:
    //  concurrent_vector(): Container<std::vector<Elem>,Elem>() {}
    using Container<std::vector<Elem>>::Container;
    void push_back(Elem& value){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->collection_.push_back(value);
        lock.unlock();
        this->cv_.notify_one();
    }
    Elem pop_back(){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->cv_.wait(lock,[this](){ return !(this->collection_.empty() ); });
        Elem& el = this->collection_.back();
        this->collection_.pop_back();
        lock.unlock();
        return el;
    }
    template<class ConstIt,class InputIt>
    void insert(ConstIt position,InputIt first,InputIt last){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->collection_.insert(position,first,last);
        lock.unlock();
        this->cv_.notify_all();
    }
    size_t size(){
        return this->collection_.size();
    }

};

template <class Elem>
class concurrent_set: public Container<std::set<Elem>>
{
public:
    using Container<std::set<Elem>>::Container;
    void push_back(Elem& value){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->collection_.push_back(value);
        lock.unlock();
        this->cv_.notify_one();
    }
    Elem pop_back(){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->cv_.wait(lock,[this](){ return !(this->collection_.empty()); });
        Elem& el = this->collection_.back();
        this->collection_.pop_back();
        lock.unlock();
        return el;
    }
    template<class InputIt>
    void insert(InputIt first,InputIt last){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->collection_.insert(first,last);
        lock.unlock();
        this->cv_.notify_all();
    }
    size_t size(){
        return this->collection_.size();
    }
    //    concurrent_set(): Container<std::set<T>,T>() {}
};

template <class Key,class Value>
class concurrent_umap: public Container<std::unordered_map<Key,Value>> {
public:
    using Container<std::unordered_map<Key,Value>>::Container;
    // concurrent_umap(): Container<std::unordered_map<Key,Value>>() {}
    //    template<class InputIt>
    Value& operator[](const Key& key){
        return this->collection_[key];
    }
    void emplace(std::pair<Key,Value> pair){
        std::unique_lock<std::mutex> lock(this->mutexCollection_);
        this->collection_.emplace(pair);
        lock.unlock();
    }
};

}
#endif // CONCURRENT

