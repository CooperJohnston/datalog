//
// Created by Cooper Johnston on 3/5/24.
//
#include "Scheme.h"
#include "Tuple.h"
#pragma once
#include <set>
#include <map>
#include <algorithm>
#ifndef PROJ1_RELATION_H
#define PROJ1_RELATION_H

#endif //PROJ1_RELATION_H

using namespace std;
class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }
    string g_name()const {
        return name;
    }
    string toString() const {
        stringstream out;

        for (auto itr : tuples)
        {
            if (!itr.empty()){
                out << "  ";

                out << itr.toString(scheme);

                out << '\n';
            }


        }

        return out.str();
    }
    Relation select1(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto itr : tuples)
        {
           if (itr.at(index) == value){
               result.addTuple(itr);

           }
        }
        return result;
    }
    Relation select2(int index1, int index2) const {
        Relation result(name, scheme);
        for (auto itr : tuples)
        {
            if (itr.at(index1) == itr.at(index2)){
                result.addTuple(itr);

            }
        }
        return result;
    }
    Relation project(vector<string> values, map<string, int> columns) {
        Relation r = Relation(name,values);
        set<int> b;
        for (int i =0; i< values.size(); i++){
            int column = columns.at(values.at(i));
            b.insert(column);

        }
        for (auto itr : tuples)
        {   vector<string> k;
            for(int i =0; i< itr.size(); i++){
                if(b.find(i) != b.end()){
                    k.push_back(itr.at(i));
                }
            }
            Tuple j = Tuple(k);
            r.addTuple(j);
        }
        return r;

    }
    Relation rename( Scheme newScheme) {
        Relation result(name, newScheme);
        for (auto itr: tuples) {
            result.addTuple(itr);
        }
        return result;
    }
    bool is_empty(){
        if (tuples.size() == 0){
            return true;
        }
        else {
            return false;
        }
    }
    int size(){
        return tuples.size();
    }
};
