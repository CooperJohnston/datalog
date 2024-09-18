//
// Created by Cooper Johnston on 3/5/24.
//
#include <vector>
#include <string>
#include "Scheme.h"
#include <sstream>

#pragma once
#ifndef PROJ1_TUPLE_H
#define PROJ1_TUPLE_H
using namespace std;
#endif //PROJ1_TUPLE_H

class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        for (int i =0; i < tuple.size(); i++){
            out << scheme.at(i);
            out << "=";
            out << tuple.at(i);
            if (i < tuple.size() - 1){
                out <<", ";
            }

        }
        return out.str();
    }


};
