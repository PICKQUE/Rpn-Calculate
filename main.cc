#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "expr.h"

void input(Expr *&,string&);


int main(){
    string s;
    
    Expr *e = new Expr("",nullptr);
    cin >> e;
    input(e,s);
    cout<<"..."<<endl;
    Expr *other=new Expr(*e);
    input(other,s);
    delete e;
}
void input(Expr *& e,string& s){
     // Command interpreter
    while (cin >> s) {
        if (s == "eval") {
            std::string unset = e->unsettedVal();
            if(unset == ""){
                int print_val = e->eval();
                cout << print_val << endl;
            }else{
                stringstream iss(unset);
                string unset_var;
                iss >> unset_var;
                cout << unset_var << " has no value." << endl;
            }
            
        }
        else if (s == "set") {
            
            string target;
            cin >> target;
            string val;
            cin >> val;
            std::istringstream ss(val);
            int n;
            ss >> n;
            e->set(target, n);
            
        }
        else if (s == "unset") {
            string target;
            cin >> target;
            e->unset(target); 
        }
        else if (s == "print") {
            cout << e->print() << endl;
        }
        else if(s=="exit"){
           return;
        }
    }

}