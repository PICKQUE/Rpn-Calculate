#include "variable.h"

variable::variable(std::string data): Node{data}, val_set(false), val(0){}

variable::variable(const variable& v):Node(v){
    val_set=v.val_set;
    val=v.val;
}
    
std::string variable::print(){
    if(val_set){
        return std::to_string(val);
    }else{
        return getData();
        
    }
}

int variable::eval(){
    if(val_set){
        return val;
    }else{
        return 0;
    }
}

void variable::set(std::string target, int n){
    if(target == getData()){
        val_set = true;
        val = n;
    }
}

void variable::unset(std::string target){
    if(target == getData()){
        val_set = false;
    }
}
