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
#ifndef DIALOG_H
#define DIALOG_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <functional>

class Dialog
{
public:
    enum class Command{
        EXIT = 0
    };

public:
    Dialog();

    //template <class Func>
    static void prompt(const std::string& prompt,
                       std::function<bool(const std::string input)> callback,
                       int max = 3,
                       const std::string& maxMsg = "Well, that was fun... Bye!",
                       std::function<bool(const std::string input)> exitPredicate = &Dialog::exitPredicate){
        try{
            std::string input;
            int step = 1;
            bool isOk = false;
            do{
                std::cout << prompt << (max ? " (try "+ std::to_string(step) + "/"+ std::to_string(max) + ")": "")<< std::endl;
                std::getline(std::cin,input);
                std::transform(input.begin(),input.end(),input.begin(),::tolower);
                step++;
            }while( !exitPredicate(input) &&  !(isOk = callback(input))  && step <= (max? max: step) ) ;
            if(!isOk){
                std::cout << maxMsg << std::endl;
                throw Dialog::Command::EXIT;
            }

        }catch(std::exception e){
            std::cout<< "Last input almost killed me..." << std::endl;
            Dialog::prompt(prompt,callback,max,maxMsg,exitPredicate);
        }

    }
    static bool exitPredicate(const std::string input){
        static std::set<std::string> set({"quit","q","exit"});
        return (set.find(input) != set.end());
    }


};

#endif // DIALOG_H
