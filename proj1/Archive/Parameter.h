//
// Created by Cooper Johnston on 2/13/24.
//
#include <string>
#ifndef PROJ1_PARAMETER_H
#define PROJ1_PARAMETER_H
using namespace std;

class Parameter {
public:
    bool isConstant;
    string name;
    Parameter(string n): name(n) {
        if (name[0] == '\'' ){
            isConstant = true;
        }
        else {
            isConstant = false;
        }
    }




};


#endif //PROJ1_PARAMETER_H
