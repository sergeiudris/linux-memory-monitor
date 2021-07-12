#ifndef _PROCESS_H
#define _PROCESS_H

#include "io.hpp"
#include <string>
#include <unordered_map>
#include "text.hpp"
#include "pageset.hpp"
#include "page.hpp"
#include <unistd.h>
#include <numeric>


#define PAGEMAP_ENTRY 8
#define PAGE_SIZE sysconf(_SC_PAGESIZE)

namespace iproc{


class Process{

public :
    Process(){}
    Process(const int& pid,const std::string& cmdline): pid_(pid),cmdline_(cmdline){}
    virtual ~Process() { }
    bool operator==(const Process& rhs){
        return (pid_ == rhs.pid_);
    }

public:
    uint_least32_t pid_;
    std::string cmdline_;
    std::vector<pageset> pageSets_;
    std::vector<page> pages_;
    uint_least64_t pss_;
    uint_least64_t rss_;

    static std::string readCmdline(int pid){
        std::string path = "/proc/"+std::to_string(pid)+"/cmdline";
        std::vector<std::string> lines;
        io::readTextFile(path,[&](const std::string& line){
            lines.push_back(line);
        });
        return lines.size()? text::split(lines[0],' ')[0] +"...":"empty";
    }

    void parseMaps(){

        std::string pathMaps = "/proc/"+std::to_string(pid_)+"/maps";
        io::readTextFile(pathMaps,[&](const std::string& line) {
            std::vector<std::string> tokens =  text::split(line,' ');
            std::vector<std::string> addresses =  text::split(tokens[0],'-');
            pageset set;
            set.address_from = text::string16ToUint64( addresses[0]);
            set.address_to = text::string16ToUint64( addresses[1]);
            pageSets_.push_back(set);
        });
    }

    void parsePagemap(){

        std::string pathPagemap = "/proc/"+std::to_string(pid_)+"/pagemap";

        FILE* pagemap = fopen(pathPagemap.c_str(),"rb");

        if(pagemap){
            for(auto& pset: pageSets_){
                uint_least64_t from = pset.address_from/PAGE_SIZE;
                uint_least64_t to = pset.address_to/PAGE_SIZE;
                uint_least64_t range = to - from;
                uint_least64_t buffer[range];
                fseek(pagemap, from*PAGEMAP_ENTRY,SEEK_SET);
                fread(&buffer,PAGEMAP_ENTRY,range,pagemap);
                for(uint_least64_t i = 0 ; i < range;i++){
                    if(getBit(buffer[i],63) && !getBit(buffer[i],62)){
                        uint_least64_t address = i*PAGE_SIZE;
                        uint_least64_t pfn = buffer[i]&0x7FFFFFFFFFFFFF;
                        pages_.emplace_back(address,buffer[i],pfn);
                    }
                }
            }
             fclose(pagemap);
        }


    }

    void parseSmaps(){
        pss_ = 0;
        rss_ = 0;
        std::string pathSmaps = "/proc/"+std::to_string(pid_)+"/smaps";
        io::readTextFile(pathSmaps,[&](const std::string& line) {
            if(line.find("Pss:") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                pss_ += tokens.size()? std::stoull(tokens[0],NULL,0): 0;
            }else if(line.find("Rss:") != std::string::npos){
                auto tokens = text::match(line,"\\d+");
                rss_ += tokens.size()? std::stoull(tokens[0],NULL,0): 0;
            }
        });
    }

    void printMeasurements(){
         printf("  pid: %d, rss: %d\ncommadnline: [%s]\n",pid_,pages_.size()*PAGE_SIZE,cmdline_.c_str());
    }

    void saveToFile(const std::string& fileName){
        io::appendToTextFile(fileName,[&,this](auto& fs){
            fs << "---" << std::endl;
            fs << "Process id: " << pid_ << std::endl;
            fs << "Distinct rss: " << pages_.size()*PAGE_SIZE/1024 << " kb" << std::endl;
            fs << "Pss: " << pss_ << " kb" <<  std::endl;
        });
    }

    uint_least64_t getBit(uint_least64_t& bits,int bitNumber){
        return ((bits & ((uint_least64_t)1<<bitNumber)) >> bitNumber);
    }



};

}

#endif // _PROCESS_H
