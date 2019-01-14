/****************************************************************************
**
** Copyright (C) 2016 Serge Joggen.
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
#ifndef GROUP_H
#define GROUP_H

#include <string>

#include <atomic>
#include <cstdint>
#include <cstdio>

#include "process.hpp"
#include "concurrent.hpp"

namespace iproc{

class Group{

public :
    Group(){}
    Group(const std::string& title): title_(title) { }
    Group(const Group& other){
        title_ = other.title_;
        pss_ = (uint_least64_t)other.pss_;
        pages_ = other.pages_;
        processes_ = other.processes_;
    }
    virtual ~Group(){ }
public:
    std::string title_;
    std::atomic<uint_least64_t> pss_;
    std::atomic<uint_least64_t> rss_;
    concurrent_set<page> pages_;
private:
    concurrent_umap<int,Process> processes_;

public:
    void addProcess(int pid,std::string& cmdline){
        processes_.emplace(std::make_pair(pid,Process(pid,cmdline)));
    }

    void getProcData(){
        pss_ = 0;
        rss_ = 0;
        processes_.forEachAsync([&,this](auto ref){
            auto& process = ref.get().second;
            process.parseMaps();
            process.parseSmaps();
            process.parsePagemap();
          //  process.printMeasurements();
            pages_.insert(process.pages_.begin(),process.pages_.end());
            pss_ += process.pss_;
            rss_ += process.rss_;

        });
    }

    void saveToFile(const std::string& fileName){
        io::appendToTextFile(fileName,[&,this](auto& fs){
            fs << "-----" << std::endl;
            fs << "Group name: " << title_ << std::endl;
            fs << "Distinct rss: " << pages_.size()*PAGE_SIZE/1024 << " kb" << std::endl;
            fs << "Pss: " << pss_ << " kb" <<  std::endl;
            fs << "-----" <<std::endl;
        });

        for(auto it: processes_.collection_){
            it.second.saveToFile(fileName);
        }
    }

};

}

#endif // GROUP_H
