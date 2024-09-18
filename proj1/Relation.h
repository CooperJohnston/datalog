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
#include <iostream>

#endif //PROJ1_RELATION_H

using namespace std;
class Relation {

private:

    string name;
    Scheme scheme;


public:
    Scheme schem = scheme;
    set<Tuple> tuples;
    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }
    string g_name()const {
        return name;
    }
    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                         const Tuple& leftTuple, const Tuple& rightTuple) {

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);

            //cout << "left name: " << leftName << " value: " << leftValue << endl;

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);
                if (rightName == leftName){
                    //cout << rightValue << leftValue << endl;
                    //cout << "INSDIE THIS LOOP" <<endl;
                    if (rightValue != leftValue){
                        return false;
                    }
                    //cout << "JOINING" << endl;
                }
                //cout << "right name: " << rightName << " value: " << rightValue << endl;

            }
        }

        return true;
    }

    Tuple add_tuple(Scheme left, Scheme right, Tuple leftt, Tuple rightt){
        Tuple ne = leftt;
        for (int i = 0; i < right.size(); i++){
            if (find(left.nam.begin(), left.nam.end(), right.at(i)) == left.nam.end()){
                //cout << right.at(i) <<endl;
                ne.push_back(rightt.at(i));
                //cout << leftt.at(left.size()-1);
            }
        }

        if (left.size() == ne.size() && right.size() > 0){
            for (auto itr: rightt){
                //cout << "oNside" <<endl;
                ne.push_back(itr);

            }
        }

        return ne;
    }
    Relation join(const Relation& right) {
        const Relation& left = *this;

        Scheme s = S_JOIN(left.scheme, right.scheme);
        //cout << "S" << s.size() <<endl;
        Relation result = Relation(left.name, s);

        for (auto itr: left.tuples){

            for (auto it : right.tuples){

                if (joinable(left.scheme, right.scheme, itr, it)){

                    Tuple t = add_tuple(left.scheme, right.scheme, itr, it);

                    //cout << t.toString(s) << endl;
                    result.addTuple(t);
                }
            }
        }
        //cout << result.toString() << endl;
        return result;
    }

    Scheme S_JOIN(Scheme left, Scheme right){
        for (int i = 0; i < right.size(); i++){
            if (find(left.nam.begin(), left.nam.end(), right.at(i)) == left.nam.end()){
                left.insert(right.at(i));
            }
        }
        return left;
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
        vector<int> b;
        for (int i =0; i< values.size(); i++){
            int column = columns.at(values.at(i));
            b.push_back(column);

        }
        for (auto itr : tuples)
        {   vector<string> k;
            for(auto it: b){
                k.push_back(itr.at(it));

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
    void unionize(Relation r){

        for (auto itr: r.tuples){
            bool b = tuples.insert(itr).second;
            if (b){
                cout << "  " << itr.toString(schem) <<endl;
            }
        }

    }
};
