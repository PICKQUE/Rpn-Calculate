#ifndef long_int_hpp
#define long_int_hpp

#include <iostream>
#include "node.h"

class long_int: public Node{
    
public:
    
    long_int(std::string data);
    long_int(const long_int&);    
    std::string print() override;
    
    int eval() override;
    
    void set(std::string target, int n) override;
    
    void unset(std::string target) override;
    
};


#endif
