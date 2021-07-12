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
