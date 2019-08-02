#include "long_int.h"


long_int::long_int(std::string data): Node{data}{}

long_int::long_int(const long_int& l):Node(l){}

std::string long_int::print(){
    return getData();
}

int long_int::eval(){
    return stoi(getData());
}

void long_int::set(std::string target, int n){
    return;
}

void long_int::unset(std::string target){ 
    return;
}
