//
// Created by Cooper Johnston on 3/12/24.
//
#include "datalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Tuple.h"
#include "Graph.h"
#include <iostream>
class interpreter {
private:
    datalogProgram program;
    Database database;

public:
    interpreter(datalogProgram db) : program(db){


    }
    void evalSchemes(){
        for (int i= 0; i<program.schemes.size(); i++){
            Scheme s = Scheme(program.schemes[i].slist());
            Relation r = Relation(program.schemes[i].name, s);
            //cout << r.toString() << endl;
            database.AddRelation(r);
        }
    }
    void evalFacts(){

        for (int i= 0; i<program.facts.size(); i++){

            Tuple t = Tuple(program.facts.at(i).slist());

            database.add_T(program.facts[i].name, t);



        }

    }
    Relation evalquery(Predicate p){
        Relation found = database.GetCopy(p.name);
        //cout << found.toString() << endl;
        map<string, int> columns;
        vector<string> order;
        for (int i = 0; i < p.plist.size(); i++){
            Parameter j = p.plist.at(i);

            if (j.isConstant){
                found = found.select1(i,j.name);
                //cout << "CONSTant" << j.name << endl;
            }
            else{
                if (columns.find(j.name) != columns.end()){
                    found = found.select2(i, columns.at(j.name));

                }
                else {
                    columns.insert(map<string, int>::value_type(j.name, i));
                    order.push_back(j.name);
                    //cout << j.name;
                }
            }


        }

        found = found.project(order, columns);
        Scheme s = Scheme(order);
        found = found.rename(s);
        return found;
    }
    void evalQs(){
        cout << "Query Evaluation" << endl;
        for (int i = 0; i< program.queries.size(); i++){
            cout << program.queries.at(i).to_string() << "? ";
            Relation r = evalquery(program.queries.at(i));
            if (r.is_empty()){
                cout << "No" <<endl;
            }
            else {
                cout << "Yes(" << r.size() << ")" <<endl;
                cout << r.toString();
            }

        }
    }
    Relation evalRule(Rule r){
        //cout << "Made it to the eval stage" << endl;
        cout << r.to_string() << "." << endl;
        vector<Relation> rlist;
        for (int i = 0; i < r.pred_list.size(); i++){
            Relation j = evalquery(r.pred_list.at(i));
            //cout << j.toString() << endl;
            rlist.push_back(j);
        }

        Relation result = rlist.at(0);
        for (int i =1; i< rlist.size(); i++){
            //cout << rlist.at(i).toString() << endl;
            result = result.join(rlist.at(i));
            //cout << result.toString() << endl;

        }
        //cout <<result.toString() << endl;
        Predicate hp = r.head_pred;
        map<string, int> columns;
        vector<string> order;
        for (int i = 0; i < hp.plist.size(); i ++){
            string id = hp.plist.at(i).name;
            //cout << id << endl;
            order.push_back(id);
            int fa = 0;
            for (int j = 0; j < result.schem.size(); j++){
                //out << j << endl;
                if (result.schem.at(j) == id){
                    break;
                }
                fa ++;

            }
            columns.insert(map<string, int>::value_type(id, fa));
        }


        result = result.project(order,columns);
        //cout << result.toString() << endl;

        Relation * g = database.GetRelation(hp.name);
        //cout<< g->schem.size() << endl;
        Relation correct = database.GetCopy(hp.name);
        //cout << correct.toString() << endl;


        result = result.rename(correct.schem);
        //cout << (*correct).toString() << endl;
        (&correct)->unionize(result);
        //cout << correct.toString() << endl;
        for (auto itr: result.tuples){
            database.add_T(correct.g_name(),itr);
        }
        return correct;
    }
    Relation EvalutatePredicate(Predicate Queries) {
        string theName = Queries.name;
        vector<int> theInts;
        vector<string> theStrings;
        map<string, int> columns;
        Relation thisRelation = database.relations.at(theName);
        for (unsigned int j = 0; j < Queries.plist.size(); j++) {
            Parameter currentParameter = Queries.plist.at(j);
            if (currentParameter.isConstant == true) {
                string yes = currentParameter.name;
                thisRelation = thisRelation.select1(j,yes);
            }
            else {
                bool duplicate = false;
                for (unsigned int k = 0; k < theStrings.size(); k++) {
                    if (theStrings.at(k) == currentParameter.name) {
                        duplicate = true;
                        thisRelation = thisRelation.select2(j,k);
                    }
                }
                if(duplicate == false) {
                    theStrings.push_back(currentParameter.name);
                    theInts.push_back(j);
                    columns.insert(map<string, int>::value_type(currentParameter.name, j));
                }
            }
        }
        thisRelation = thisRelation.project(theStrings, columns);
        thisRelation = thisRelation.rename(theStrings);
        return thisRelation;
    }

    void RelationRules(vector<Rule> Rules, bool trivial){
        bool moreTuples = true;
        int rulesPass =0;
        while (moreTuples) {
            moreTuples = false;
            vector <bool> shouldGoOn;
            rulesPass++;
            for (unsigned int i = 0; i < Rules.size(); i ++) {
                cout << Rules.at(i).to_string()<< endl;
                vector <Relation> theRelations;
                for (unsigned int j = 0; j < Rules.at(i).pred_list.size(); j ++ ) {
                    Relation thisRelation = EvalutatePredicate(Rules.at(i).pred_list.at(j));
                    theRelations.push_back(thisRelation);
                }

                // Join
                Relation thisRelation;
                if (theRelations.size() > 1) {
                    thisRelation = theRelations.at(0);
                    for (unsigned int j = 0; j < theRelations.size()-1; j++ ) {
                        thisRelation = thisRelation.Join(theRelations.at(j+1));
                    }
                }
                else {
                    thisRelation = theRelations.at(0);
                }
                //Project
                //What the heck is going on???
                vector <int> Indicies;
                for (unsigned int j = 0; j < Rules.at(i).Head.parameterList.size(); j++) {
                    //cout << Rules.at(i).Head.parameterList.at(j).ToString() << " | " << thisRelation.TheScheme.Fake();
                    for (unsigned int k = 0; k < thisRelation.TheScheme.Size(); k++) {
                        //cout << Rules.at(i).Head.parameterList.at(j).theParameter << "|" << thisRelation.TheScheme.At(k) << endl;
                        if (Rules.at(i).Head.parameterList.at(j).theParameter == thisRelation.TheScheme.At(k)) {
                            Indicies.push_back(k);
                            //cout << "got pushed back" << endl;
                        }
                    }
                }
                //cout << "indicies: " <<Indicies.size() << endl;
                thisRelation = thisRelation.Project(Indicies);
                //Rename
                thisRelation.name = Rules.at(i).Head.Name;
                if (theDatabase.databaseseses.at(thisRelation.name).TheScheme.values.size() == thisRelation.TheScheme.values.size()) {
                    thisRelation.TheScheme = theDatabase.databaseseses.at(thisRelation.name).TheScheme;
                }
                else {
                    //cout << "abort" << endl;
                }
                /*
                cout << "Scheme end:" ;
                for (unsigned int i = 0; i < theDatabase.databaseseses.at(thisRelation.name).TheScheme.values.size(); i++) {
                    cout << theDatabase.databaseseses.at(thisRelation.name).TheScheme.values.at(i);
                }
                cout << endl;
                thisRelation.Rename(theDatabase.databaseseses.at(thisRelation.name).TheScheme.values);
                cout << "Scheme end:" ;
                for (unsigned int i = 0; i < thisRelation.TheScheme.values.size(); i++) {
                    cout << thisRelation.TheScheme.values.at(i);
                }
                */
                //Union
                shouldGoOn.push_back(theDatabase.databaseseses.at(thisRelation.name).Unite(thisRelation));

                //output
                /*
                if (theDatabase.databaseseses.at(thisRelation.name).DemTuples.size() == 0) {}
                else {
                    if (theDatabase.databaseseses.at(thisRelation.name).BeenOutPutted == false) {
                        thisRelation.ToString();
                    }
                }
                */
            }
            for (unsigned int a = 0; a <shouldGoOn.size(); a++) {
                if (shouldGoOn.at(a)) {
                    moreTuples = true;
                }
            }/*
        if (moreTuples) {
            cout << "should have more tuples" << endl;
        }
        else {
            cout << "no more tuples" <<  endl;
        }*/
            if (!trivial) {
                moreTuples = false;
                //cout << "IN EVALUATOR SAYS TRIVIAL !!!!!" <<endl;
            }
        }
        cout << rulesPass << " passes: ";
        return;
    }

    void evalRules(vector<Rule> Rules){

        int count = 0;
        //cout << program.rules.at(0).to_string() << endl;
        //find the number of tuples in the relations
        while (true) {
            int prev = database.tupleCount();
            //cout << "DEBUG in the loop!" << endl;
            for (int i = 0; i < Rules.size(); i++) {
                //cout << "DEBUG in the loop!" << endl;
                Relation newRule = evalRule(Rules.at(i));

            }
            int cur = database.tupleCount();
            count ++;
            if (prev == cur){
                break;
            }
        }



    }
    static Graph makeGraph(const vector<Rule>& rules) {

        Graph graph(rules.size());
        int count = 0;
        for (int i = 0; i < rules.size(); i++) {
            //bool nodeAddedBackwards = false;
            int open1 = rules.at(i).pred_list.size();
            for (int j = 0; j < open1; j++) {
                for (int k = 0; k < rules.size(); k++) {
                    if (rules.at(i).pred_list.at(j).name == rules.at(k).head_pred.name) {
                        bool dependent = false;
                        //cout << i<< ":";
                        if (i == k) {
                            dependent = true;
                        }
                        if (graph.nodes[i].isDependent) {
                            dependent = true;
                        }
                        graph.addEdge(i, k, dependent);
                        //cout <<"backward from: " << k << " to: " << i << endl;

                    }
                }
            }
        }
        return graph;
    }


    void evalSCC(const vector<Rule>& rules){

            Graph  reverse = makeGraph(rules);
            Graph  regular = makeGraph(rules);

            reverse.nodes = regular.reverseNodes;
            cout << regular.tonString() << endl;
            //cout << "in here now" << endl;
            reverse.dfs_forest();
            //cout << "in here now" << endl;
            regular.postorder = reverse.postorder;
            //cout << "in here now" << endl;
            regular.dfs_norm();
            //cout << "in here now" << endl;
            cout <<endl<< "Rule Evaluation" << endl;
            for(int i = 0; i < regular.SCC.size(); i++){
                vector<Rule> rlist;
                string result;
                int count = 0;
                bool triv;
                for (auto itr: regular.SCC.at(i)){
                    rlist.push_back(rules.at(itr));
                    string name = to_string(itr);
                    result += "R";
                    result += name;
                    if (count != regular.SCC.at(i).size() -1){
                        result += ",";
                    }
                    count ++;
                    triv = reverse.nodes[itr].isDependent;

                }
                if (regular.SCC.at(i).size()!= 1){
                    triv = true;
                }
                cout <<"SCC: " << result << endl;
                evalRules(rlist);
                cout <<result << endl;

            }

        }



};