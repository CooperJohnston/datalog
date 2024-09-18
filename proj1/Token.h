//
// Created by Cooper Johnston on 1/22/24.
//
#pragma once
#ifndef CS236_TOKEN_H
#define CS236_TOKEN_H

#endif //CS236_TOKEN_H
#include <sstream>
#include <string>

#define stringify( name ) # name
using namespace std;

enum TokenType {
    COMMA, COLON, ID, LEFT_PAREN, STRING, RIGHT_PAREN, PERIOD, Q_MARK, COLON_DASH, MUlTIPLY, ADD, SCHEMES,
    FACTS, RULES, QUERIES, COMMENT, EO , UNDEFINED
};

const char* TokenTypeNames[]= {
        stringify(COMMA),
        stringify(COLON),
        stringify(ID),
        stringify(LEFT_PAREN),
        stringify(STRING),
        stringify(RIGHT_PAREN),
        stringify(PERIOD),
        stringify(Q_MARK),
        stringify(COLON_DASH),
        stringify(MUlTIPLY),
        stringify(ADD),
        stringify(SCHEMES),
        stringify(FACTS),
        stringify(RULES),
        stringify(QUERIES),
        stringify(COMMENT),
        stringify(EO),
        stringify(UNDEFINED)
};

class Token {
private:
    TokenType type;
    string icon;
    int line;

public:
    Token(TokenType t, string i, int l) : type(t), icon(i), line(l){



    }
    TokenType tipe = type;
    string ico = icon;
    string toString() const {
        stringstream out;
        if (type == EO){
            out << "(" << "EOF" << "," << "\"" << icon << "\"" <<"," << line << ")";
            return out.str();
        }
        out << "(" << TokenTypeNames[type] << "," << "\"" << icon << "\"" <<"," << line << ")";
        return out.str();
    }

};