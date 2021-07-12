#include "dialog.hpp"
#include <cstdint>
#include <vector>
#include <string>
#include <iproc/text.hpp>
#include <iproc/procinterface.hpp>
#include <iproc/message.hpp>
#include <thread>
#include <chrono>
#include <future>
#include <cstdio>
#include <cstdlib>


int askIproc();

int main()
{
    int disturbanceInTheForce = 1;
    do{
        disturbanceInTheForce = askIproc();
    }while(disturbanceInTheForce);

    return 0;

}

int askIproc(){

    std::cout << "Hi! This program calculates the RAM consumtion by a group of processes." << std::endl;
    std::cout << "Enter 'q' or 'quit' at any stage to exit." << std::endl;
    std::cout << "Warning: remove files from previous data capture. You may do it now." << std::endl;
    try{

        //        bool isOk = false;
        uint_least32_t period = 1;
        uint_least32_t interval = 1;
        std::string duration;

        std::vector<std::string> titles;
        iproc::ProcInterface p;
        uint_least32_t pidCount = 0;
        Dialog::prompt("Enter processes names, separated by spaces (i.e. 'chrome firefox skype'):",[&](auto input){
            titles = iproc::text::split(input,' ');
            pidCount =  p.getPids(titles);
            if(!pidCount){
                printf("No such processes...\n");
            }
            return pidCount;
        },0);

        Dialog::prompt("One measurement or over a period of time? ['one' or 'period']:",[&](auto input){
            duration = input;
            return (input == "one" || input == "period");
        });

        if(duration == "period"){
            Dialog::prompt("Enter period length in seconds(i.e.600):",[&](auto input){
                uint_least32_t num = strtoul(input.c_str(),NULL,0);
                period = num;
                return num;
            });
            Dialog::prompt("Enter interval (=step) length in seconds(i.e.60):",[&](auto input){
                uint_least32_t num = strtoul(input.c_str(),NULL,0);
                interval = num;
                return num;
            });
        }
        bool saveToFiles = false;
        Dialog::prompt("Save to data to files?['yes' or 'no']:",[&](auto input){
            if(input == "yes"){
                saveToFiles = true;
                return true;
            }else if(input == "no"){
                return true;
            } else{
                return false;
            }


        });

        std::string directory = saveToFiles? iproc::text::getDateTimeStr() :"";
        printf("Starting calculation...\n");
        int steps = period/interval;
        steps = steps ? steps: 1;
        int step = 1;
        while(step <= steps){
            printf(" step %d/%d\n",step,steps);
            step++;
            auto f = std::async(std::launch::async,&iproc::ProcInterface::calculateForTitles,&p,titles,directory);
            //  iproc::message msg = p.calculateForTitles(titles,directory);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval*1000));
            auto msg = f.get();
            printf("%s\n",msg.toString().c_str());
        }

        return (int)Dialog::Command::EXIT;

    }catch(std::exception ex){
        std::cout << ex.what() << std::endl;
    }catch(Dialog::Command cmd){
        return (int)cmd;
    }

}
