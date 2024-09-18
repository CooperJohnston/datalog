//
// Created by Cooper Johnston on 2/13/24.
//

#ifndef PROJ1_DATALOGPROGRAM_H
#define PROJ1_DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <set>

using namespace std;

class datalogProgram{
public:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domains;
string to_string(){
    string st = "Success!\n";
    st += "Schemes(";
    st += std::to_string(schemes.size());
    st+= "):\n";
    for (int i = 0; i < schemes.size(); i++) {
        st += "  ";
        st += schemes[i].to_string();
        st += "\n";

    }

    st += "Facts(";
    st += std::to_string(facts.size());
    st+= "):\n";
    for (int i = 0; i < facts.size(); i++) {
        st += "  ";
        st += facts[i].to_string();
        st += ".";
        st += "\n";

    }
    st += "Rules(";
    st += std::to_string(rules.size());
    st+= "):\n";
    for (int i = 0; i < rules.size(); i++) {
        st += "  ";
        st += rules[i].to_string();
        st += ".";
        st += "\n";
    }
    st += "Queries(";
    st += std::to_string(queries.size());
    st+= "):\n";
    for (int i = 0; i < queries.size(); i++) {
        st += "  ";
        st += queries[i].to_string();
        st += "?";
        st += "\n";
    }
    st += "Domain(";
    st += std::to_string(domains.size());
    st+= "):\n";
    auto it = domains.begin();
    for (int i=0; i<domains.size();i++){
        st += "  ";
        st += *it;
        if (i != domains.size()-1){
            st += "\n";
        }
        it ++;
    }

    return st;
}
};



#endif //PROJ1_DATALOGPROGRAM_H
