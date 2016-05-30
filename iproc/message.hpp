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
#ifndef MESSAGE
#define MESSAGE

#include <cstdint>
#include "meminfo.hpp"
#include <string>
#include <sstream>
namespace iproc{

typedef struct Message {

    std::string msg;
    std::string datetime;
    std::string titles;
    uint_least64_t distinctRss;
    uint_least64_t totalRss;
    uint_least64_t pss;
    meminfo meminf;

    std::string toString(){

        std::stringstream ss;

        ss << datetime << std::endl;
        ss << "Total distinct rss: " << distinctRss << std::endl;
        ss << "Total pss: " << pss << std::endl;
        ss << "MemTotal: " << meminf.MemTotal <<std::endl;
        ss << "MemFree: " << meminf.MemFree <<std::endl;
        ss << "MemAvailable: " << meminf.MemAvailable <<std::endl;
        ss << "SwapTotal: " << meminf.SwapTotal <<std::endl;
        ss << "SwapFree: " << meminf.SwapFree <<std::endl;

        return ss.str();
    }


} message;

}


#endif // MESSAGE

