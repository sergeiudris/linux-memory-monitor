/****************************************************************************
**
** Copyright (C) 2015 sergeiudris
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
#ifndef TEXT_H
#define TEXT_H

#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <regex>
#include <iostream>
#include <time.h>
#include <unistd.h>
namespace iproc {

namespace text{

inline std::vector<std::string> split(const std::string& str, char delim){
    std::vector<std::string> result;
    std::string part;
    std::stringstream ss(str);
    while(std::getline(ss,part,delim)){
        result.push_back(part);
    }
    return result;
}
inline std::string join(const std::vector<std::string> v, char delim = ','){
    std::string result;
    for(auto& s: v){
        result += (s+delim);
    }
    return result;
}
inline std::vector<std::string> match(const std::string& subject,const std::string& regex){

    std::vector<std::string> result;

    std::smatch matches;
    std::regex_search(subject,matches,std::regex(regex));
    for(size_t i = 0; i< matches.size();i++){
        result.push_back(matches.str(i));
    }


    return result;
}

inline uint64_t string16ToUint64(const std::string& str){
    std::string s("0x");
    s = str.substr(0,2) != s ? s.append(str) : str;
    uint64_t result = strtoull(s.c_str(),NULL,0);
    return result;
}

inline std::string getDateTimeStr() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return std::string(buf);
}


}
}

#endif // TEXT_H
