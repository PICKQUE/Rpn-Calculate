#ifndef variable_hpp
#define variable_hpp
#include <iostream>
#include "node.h"


class variable: public Node{
    
    bool val_set;
    
    int val;
    
public:

    variable(std::string data);
    
    variable(const variable&);
    
    std::string print() override;
    
    int eval() override;
    
    void set(std::string target, int n) override;
    
    void unset(std::string target) override;
    
};

#endif /* variable_hpp */
