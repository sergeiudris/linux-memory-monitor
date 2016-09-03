/****************************************************************************
**
** Copyright (C) 2016 Serge Joggen.
** Contact: serge.joggen@gmail.com
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
#ifndef MEMINFO
#define MEMINFO

#include <cstdint>

#include "io.hpp"
#include "text.hpp"

namespace iproc{

typedef struct Meminfo {

    /* lets select most meaningful stats */
    uint_least64_t MemTotal;
    uint_least64_t MemFree;
    uint_least64_t MemAvailable;
    uint_least64_t SwapTotal;
    uint_least64_t SwapFree;

    void parseMeminfo(){
        io::readTextFile("/proc/meminfo",[&,this](auto& line){
            if(line.find("MemTotal") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                MemTotal = tokens.size()? std::stoull(tokens[0],NULL,0) : 0;
            }else if(line.find("MemFree") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                MemFree = tokens.size()? std::stoull(tokens[0],NULL,0) : 0;
            }else if(line.find("MemAvailable") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                MemAvailable = tokens.size()? std::stoull(tokens[0],NULL,0) : 0;
            }else if(line.find("SwapTotal") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                SwapTotal = tokens.size()? std::stoull(tokens[0],NULL,0) : 0;
            }else if(line.find("SwapFree") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                SwapFree = tokens.size()? std::stoull(tokens[0],NULL,0) : 0;
            }
        });
    }

} meminfo;

}

#endif // MEMINFO

