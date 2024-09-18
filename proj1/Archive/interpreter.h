//
// Created by Cooper Johnston on 3/12/24.
//
#include "datalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Tuple.h"
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
};