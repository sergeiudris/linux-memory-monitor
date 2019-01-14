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
#ifndef _IO_H
#define _IO_H

#include <string>
#include <vector>

#include <functional>
#include <fstream>
#include <dirent.h>
#include <cstdio>
#include <sys/stat.h>

namespace iproc{

namespace io{

inline void readTextFile(const std::string& fileName,std::function<void(const std::string&)> lineCallback){

    std::fstream file(fileName.c_str(),std::fstream::in);
    std::string line;
    if(file.is_open()){

        while(std::getline(file,line)){
            lineCallback(line);
        }

        file.close();
    }
    return;
}

inline void appendToTextFile(const std::string& fileName,std::function<void(std::fstream& fs)> callback){
    mode_t processMask = umask(0);
    std::fstream file(fileName.c_str(),std::fstream::out|std::fstream::app);
    if(file.is_open()){
        callback(file);
    }
    file.close();
    umask(processMask);
}

inline std::vector<std::string> getDirEntries(const std::string& path){


    std::vector<std::string> out;

    DIR* directory = opendir(path.c_str());
    if(directory != NULL){
        try{
        struct dirent* entry;
        while( (entry = readdir(directory) )){
            out.push_back(std::string(entry->d_name));
        }
        }catch(std::exception e){
            printf(e.what());
        }
    }
    return out;
}

inline bool directoryExists(const std::string& path){
    struct stat sb;
    if(stat(path.c_str(),&sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    return false;
}

inline bool tryMakeDirectory(const std::string& path){
    if(!directoryExists(path)){
        mode_t processMask = umask(0);
        mkdir(path.c_str(),0777);
        umask(processMask);
    }
}

}

}

#endif // _IO_H
