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
