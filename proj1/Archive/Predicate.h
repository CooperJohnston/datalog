//
// Created by Cooper Johnston on 2/13/24.
//
#include "Parameter.h"
#ifndef PROJ1_PREDICATE_H
#define PROJ1_PREDICATE_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#pragma once

using namespace std;
class Predicate {
public:
    string name;
    vector<Parameter> plist;
    Predicate(string n) : name(n) {

    };
    string to_string() const {
        stringstream out;
        out << name << "(";
        for (int i = 0; i < plist.size(); i ++){
            out << plist[i].name;
            if (i != plist.size()-1){
            out << ","; }
        }
        out << ")";
        return out.str();
    }
    vector<string> slist(){
        vector<string> v;
        for (int i = 0; i < plist.size(); i ++){
            v.push_back(plist[i].name);

        }
        return v;
    }

};


#endif //PROJ1_PREDICATE_H
