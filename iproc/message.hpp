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

