//
// Created by Cooper Johnston on 2/6/24.
//
#include "Token.h"
#ifndef PROJ1_PARSER_H
#define PROJ1_PARSER_H
#include <list>
#include <iostream>
#include <vector>
#include "datalogProgram.h"
#include <algorithm>

class Parser {
private:
    vector<Token> tokens;
public:
    vector<Token> toke = tokens;
    Parser(const vector<Token>& tokens) : tokens(tokens) { }
    //datalogProgram db;
    TokenType tokenType() const {
        return tokens.at(0).tipe;
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    void throwError() {
        throw(tokens.at(0));
    }
    void match(TokenType t) {
        //cout << "match: " << t << endl;
        // add code for matching token type t
        if (tokenType() == t){
                advanceToken();
        }
        else {throwError();}
    }
    void idList(vector<Parameter> &p) {
        if (tokenType() == COMMA) {
            //cout << "in ID LIST " << endl;
            match(COMMA);
            Parameter j = Parameter(tokens.at(0).ico);
            //cout << j.name << endl;
            match(ID);
            p.push_back(j);
            idList(p);
        } else {
            // lambda
        }
    }
    Predicate scheme(){
        Predicate p = Predicate(tokens.at(0).ico);

        match(ID);

        match(LEFT_PAREN);

        Parameter j = Parameter(tokens.at(0).ico);
        //cout << tokens.at(0).ico << endl;
        p.plist.push_back(j);
        //cout << tokens.at(0).ico << endl;
        match(ID);
        idList(p.plist);

        match(RIGHT_PAREN);
        //cout << p.to_string() << endl;
        return p;


    }
    void schemeList(vector<Predicate> &p) {
        if(tokenType() == ID){
            //cout << "IN SCHEME BITCH" << endl;
            p.push_back(scheme());
            schemeList(p);
        }
        else {
            //lambda
        }
    }
    void stringList(vector<Parameter> &p){
        if (tokenType() == COMMA){
            match(COMMA);
            Parameter j = Parameter(tokens.at(0).ico);
            p.push_back(j);
            match(STRING);
            stringList(p);
        }
        else {

        }

    }
    Predicate fact(){
        Predicate p = Predicate(tokens.at(0).ico);
        match(ID);
        match(LEFT_PAREN);
        Parameter j = Parameter(tokens.at(0).ico);
        p.plist.push_back(j);
        match(STRING);
        stringList(p.plist);
        match(RIGHT_PAREN);
        match(PERIOD);
        return p;
    }
     Parameter parameter(){
        if(tokenType() == STRING){
            Parameter p = Parameter(tokens.at(0).ico);
            match(STRING);
            return p;
        }
        else {
            Parameter p = Parameter(tokens.at(0).ico);
            match(ID);
            return p;
        }
    }
    void parameterList(vector<Parameter> &p){
        if (tokenType()== COMMA){
            match(COMMA);
            p.push_back(parameter());
            parameterList(p);
        }
        else{

        }
    }
    Predicate predicate(){
        Predicate p = Predicate(tokens.at(0).ico);
        match(ID);
        match(LEFT_PAREN);
        p.plist.push_back(parameter());
        parameterList(p.plist);
        match(RIGHT_PAREN);
        return p;
    }
    void predicateList(vector<Predicate> &p){
        if (tokenType()==COMMA){
            match(COMMA);
            p.push_back(predicate());
            predicateList(p);
        }
        else {

        }

    }
    Predicate headPredicate(){
        Predicate p = Predicate(tokens.at(0).ico);
        match(ID);
        match(LEFT_PAREN);
        Parameter j = Parameter(tokens.at(0).ico);
        p.plist.push_back(j);
        match(ID);
        idList(p.plist);
        match(RIGHT_PAREN);
        return p;
    }
    Predicate query(){
        Predicate j = predicate();
        match(Q_MARK);
        return j;
    }
    Rule rule(){
        Rule r = Rule(headPredicate());
        match(COLON_DASH);

        r.pred_list.push_back(predicate());
        predicateList(r.pred_list);
        match(PERIOD);
        return r;
    }
    void queryList(vector<Predicate> &p){
        if (tokenType() == ID){
            p.push_back(query());
            queryList(p);
        }
        else{

        }
    }

    void ruleList(vector<Rule> &p){
        if (tokenType() == ID){
            p.push_back(rule());
            ruleList(p);
        }
        else {

        }
    }
    void factList(vector<Predicate> &p){
        if (tokenType()==ID){
            p.push_back(fact());
            factList(p);
        }
        else {

        }
    }
    datalogProgram parse(){
        try {

            datalogProgram db;
            match(SCHEMES);
            match(COLON);
            //cout << "DEbug" << endl;
            //cout << "BOB" << endl;
            db.schemes.push_back((scheme()));
            //cout << db.schemes.at(0).name<< endl;
            schemeList(db.schemes);
            match(FACTS);
            match(COLON);
            //db.facts.push_back(fact());
            //cout << "DEBUG, I am checking to see my fact list" << endl;
            //cout << db.facts.at(0).to_string() << endl;
            factList(db.facts);
            //cout << "DEBUG, I am checking to see my fact list" << endl;
            //cout << db.facts.at(1).to_string() << endl;
            for (int i = 0; i < db.facts.size(); i++) {
                for (int j = 0; j < db.facts[i].plist.size(); j++) {
                    db.domains.insert(db.facts[i].plist[j].name);
                }
            }
            match(RULES);
            match(COLON);
            //db.rules.push_back(rule());
            ruleList(db.rules);
            match(QUERIES);
            match(COLON);
            db.queries.push_back(query());
            queryList(db.queries);
            match(EO);
            //cout << "DEBUG MADE IT OUT " << endl;
            return db;
        }
        catch (Token t) {
            datalogProgram db;
            cout << "Failure!" <<endl;
            cout << "  " << t.toString() << endl;
            return db;
        }
    }
};



#endif //PROJ1_PARSER_H
