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
#ifndef PROCINTERFACE_H
#define PROCINTERFACE_H

#include <vector>
#include "arithm.hpp"
#include <string>
#include "group.hpp"
#include <mutex>
#include <cstdint>
#include <atomic>
#include "message.hpp"
#include <thread>

namespace iproc {

class ProcInterface
{
public:
    ProcInterface(): pss_(0){}
    virtual ~ProcInterface(){}
private:
    concurrent_umap<std::string,Group> groups_;
    concurrent_set<page> pages_;
    std::atomic<uint_least64_t> pss_;
    std::atomic<uint_least64_t> rss_;
    meminfo meminfo_;



    void getProcData(){

        //printf("starting to collect processes' data async...\n");
        pss_ = 0;
        rss_ = 0;
        pages_.collection_.clear();;
        groups_.forEachAsync([&,this](auto ref){
            auto& group = ref.get().second;
            group.getProcData();
            pages_.insert(group.pages_.begin(),group.pages_.end());
            pss_ += group.pss_;
            rss_ += group.rss_;
        });
    }

    void saveToFile(const std::string directory){
        io::tryMakeDirectory(directory);
        std::string dateTime = text::getDateTimeStr();
        std::string subPath = directory + "/" +dateTime;
        io::tryMakeDirectory(subPath);

        for(auto it: groups_.collection_){
            Group& g = it.second;
            std::string fileName(subPath+"/"+g.title_+".txt");
            g.saveToFile(fileName);
        }
        io::appendToTextFile(subPath+"/total.txt",[&,this](auto& fs){
            fs << "-----" << std::endl;
            fs << "RAM used (distinct rss): " << pages_.size()*PAGE_SIZE/1024 << " kb" << std::endl;
            fs << "Pss: " << pss_ << " kb" <<  std::endl;
            fs << "MemTotal: " << meminfo_.MemTotal<< " kb" << std::endl;
            fs << "MemFree: " << meminfo_.MemFree<< " kb" << std::endl;
            fs << "MemAvailable: " << meminfo_.MemAvailable << std::endl;
            fs << "SwapTotal: " << meminfo_.SwapTotal<< " kb" << std::endl;
            fs << "SwapFree: " << meminfo_.SwapFree<< " kb" << std::endl;
            fs << "-----" <<std::endl;
        });


    }

public:
    uint_least32_t getPids(const std::vector<std::string>& titles){
        groups_.collection_.clear();
        for(auto& t: titles){
            groups_.emplace(std::make_pair(t,Group(t)));
        }
        //printf("->reading /proc directory...\n");
        auto folders = io::getDirEntries("/proc");
        //printf("filtering pids...\n");
        auto pids = arithm::map<int>(folders,[&](auto& el,auto& i,auto& a){
            int pid = atoi(el.c_str());
            return pid > 0? pid: NULL;
        });
        //printf("filtering cmdlines...\n");
        concurrent_vector<int> concur_pids(pids);
        std::atomic<uint_least32_t> pidCount(0);
        concur_pids.forEachAsync([&](auto ref){
            int pid = ref.get();
            std::string cmdline = Process::readCmdline(pid);
            for(auto& t: titles){
                if(cmdline.find(t) != std::string::npos){
                    pidCount++;
                    groups_[t].addProcess(pid,cmdline);

                }
            }
        });
        uint_least32_t result = pidCount;
        return result;
    }

    message calculateForTitles(const std::vector<std::string>& titles,const std::string directory) {

        message result;
        getProcData();
        meminfo_.parseMeminfo();
        uint_least64_t distinctRss = pages_.size()*PAGE_SIZE/1024;
        //printf("total distinct rss: %d kb\n",distinctRss);
       // printf("total pss: %d, kb\n",(uint_least64_t)pss_);


        result.distinctRss = distinctRss;
        result.pss = pss_;
        result.totalRss = rss_;
        result.meminf = meminfo_;
        result.datetime = text::getDateTimeStr();
        result.titles = text::join(titles);
        if(!directory.empty()){
            //            std::thread save(&ProcInterface::saveToFile,this,directory);
            //            save.detach();
            saveToFile(directory);
        }

        return result;

    }


};

}

#endif // PROCINTERFACE_H
