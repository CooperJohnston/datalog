//
// Created by Cooper Johnston on 4/1/24.
//
#include <set>
#include <string>
#include <sstream>
#ifndef PROJ1_NODE_H
#define PROJ1_NODE_H
using namespace std;


class Node {



public:
    int rulen;
    set<int> adjacentNodeIDs;
    bool visited = false;
    bool isDependent = false;
    int size(){
        return adjacentNodeIDs.size();
    }
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }
    string toString(){
        stringstream out;
        int count = 0;
        for (auto itr: adjacentNodeIDs){
            out << "R" << itr;
            if (count < adjacentNodeIDs.size() -1){
                out << ",";
            }
            count ++;
        }
        return out.str();
    }

};
#endif //PROJ1_NODE_H
