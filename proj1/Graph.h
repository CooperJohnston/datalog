//
// Created by Cooper Johnston on 4/1/24.
//
#include <stack>
#include "Node.h"
#include <map>
#include <iostream>
#include <vector>
#ifndef PROJ1_GRAPH_H
#define PROJ1_GRAPH_H
class Graph {



public:
    map<int,Node> nodes;
    map<int,Node> reverseNodes;
    stack<int> postorder;
    vector< set<int> > SCC;
    set<int>fill;

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++) {
            nodes[nodeID] = Node();

        }
    }

    void addEdge(int fromNodeID, int toNodeID, bool dependent) {
        nodes[fromNodeID].addEdge(toNodeID);
        nodes.at(fromNodeID).isDependent = dependent;
        reverseNodes[toNodeID].addEdge(fromNodeID);
        reverseNodes.at(fromNodeID).isDependent = dependent;
    }
    string tonString(){
        stringstream out;
        for (auto& pair: nodes) {
            int nodeID = pair.first;
            Node node = pair.second;
            out << "R" << nodeID <<":" << node.toString() << endl;
        }
        return out.str();
    }
    string tovString(){
        stringstream out;
        for (auto& pair: reverseNodes) {
            int nodeID = pair.first;
            Node node = pair.second;
            out << "R" << nodeID <<":" << node.toString() << endl;
        }
        return out.str();
    }
    void dfs(Node& x){
        cout << x.toString() << endl;
        if (x.visited){
            return;
        }
        else {
            x.visited = true;
            //nodes.at(x.rulen).visited = true;
        for (auto itr: x.adjacentNodeIDs){
            if (nodes.at(itr).visited == false){
                dfs(nodes[itr]);
            }

        }
        postorder.push(x.rulen);
        return;
      }

    }
    void dfs_forest(){
        //cout << "IN THE JUNGLE" << endl;
        for (auto& pair: nodes) {
            int nodeID = pair.first;
            Node& node = pair.second;
            //cout << "made it to the node" << endl;
            if (not node.visited) {
                dfs(node);
            }

        }
        return;

    }

    void dfs_norm() {
        while(!postorder.empty()){
            //cout << to_string(postorder.top()) << endl;
            // following the algorithm
            if(!nodes[postorder.top()].visited){
                dfsS(nodes[postorder.top()]);
            }
            else {
                if (fill.size() != 0) {
                    //add the useed materials
                    SCC.push_back(fill);

                    fill.clear();
                }
                //cout << "POPPED: " << topologicalSearch.top() << endl;
                postorder.pop();
            }
        }
        return;
    }
    void dfsS(Node x){
        //follow pattern of the alogorithm
       if (x.visited){
           return;
       }
       else {
           // cout << "DEBUG" <<  x.rulen << endl;
           nodes.at(x.rulen).visited = true;
           fill.insert(x.rulen);

           for(auto itr: x.adjacentNodeIDs){
               if (not nodes[itr].visited){
                   dfsS(nodes[itr]);
               }
           }
           return;
       }
    }





};

#endif //PROJ1_GRAPH_H
