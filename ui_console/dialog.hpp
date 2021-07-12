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
