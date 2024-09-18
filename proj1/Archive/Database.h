//
// Created by Cooper Johnston on 3/12/24.
//
#include "Relation.h"
#include <map>

#include <string>
#include <iostream>
#pragma once
using namespace std;

class Database {
private:
    map<string, Relation>  relations;

public:
    Database(){

    }
    void AddRelation(Relation wRelation){
        string name = wRelation.g_name();

        relations.insert(map<string, Relation>::value_type(name, wRelation));

    }
    Relation* GetRelation(string Name){
        Relation found = (relations.find(Name))->second;

        Relation * chuck = &(found);

        return chuck;
    }
    void add_T(string Name, Tuple t){
        //cout << "adding a touple" << endl;
        Relation found = (relations.find(Name))->second;
        found.addTuple(t);
        (relations.find(Name))->second = found;

    }
    Relation GetCopy(string Name){
        Relation found = (relations.find(Name))->second;
        return found;

    }

};