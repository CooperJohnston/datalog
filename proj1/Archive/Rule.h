//
// Created by Cooper Johnston on 2/13/24.
//
#include "Predicate.h"
#ifndef PROJ1_RULE_H
#define PROJ1_RULE_H
#include <vector>
#pragma once

using namespace std;
class Rule{
public:
    Predicate head_pred;
    vector<Predicate> pred_list;
    Rule(Predicate p): head_pred(p){}
    string to_string() const {
        stringstream out;
        out << head_pred.to_string() << " :- ";
        for (int i = 0; i < pred_list.size(); i ++){
            out << pred_list[i].to_string();
            if (i != pred_list.size()-1){
                out << ","; }
        }
        return out.str();
    }
};




#endif //PROJ1_RULE_H
