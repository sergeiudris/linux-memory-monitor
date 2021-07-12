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
