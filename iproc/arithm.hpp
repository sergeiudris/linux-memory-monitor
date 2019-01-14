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
#ifndef ARITHM_H
#define ARITHM_H

#include <algorithm>
//#include <functional>

namespace iproc{

namespace arithm {

template<class Vec,class Pred >
inline Vec filter(Vec& in, Pred predicate){
    Vec out(in.size());
    auto it = std::copy_if(in.begin(),in.end(),out.begin(),predicate);
    out.resize(std::distance(out.begin(),it));
    return out;
}

template<class Type,class Vec,class Func>
inline std::vector<Type> map(Vec& in, Func modifier){
    std::vector<Type> out(in.size());
    uint32_t j = 0;
    for(uint32_t i = 0; i < in.size();i++){
        Type value = modifier(in[i],i,in);
        if(value != false || value != NULL){
            out[j++] = value;
        }
    }
    out.resize(j);
    return out;
}


}


}




#endif // ARITHM_H
