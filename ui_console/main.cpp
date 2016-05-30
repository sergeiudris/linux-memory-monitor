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
