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

