//
// Created by Cooper Johnston on 3/5/24.
//
#include <string>
#include <vector>
#include "Parameter.h"
#ifndef PROJ1_SCHEME_H
#define PROJ1_SCHEME_H
#pragma once
#endif //PROJ1_SCHEME_H
using namespace std;
class Scheme {

private:

    vector<string> names;

public:
    vector<string> nam;

    Scheme(vector<string> names) : names(names) {nam = names; }

    unsigned size() const {
        return names.size();
    }

    const string& at(int index) const {
        return names.at(index);
    }
    void insert(string name){
        names.push_back(name);
    }

    // TODO: add more delegation functions as needed

};