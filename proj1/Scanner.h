//
// Created by Cooper Johnston on 1/22/24.
//

#ifndef CS236_SCANNER_H
#define CS236_SCANNER_H

#endif //CS236_SCANNER_H
#pragma once
#include <list>
#include <string>
#include "Token.h"
#include <cctype>
#include <iostream>

class Scanner {
private:
    string input;
    vector<Token> token_list;
    int line;
    //int tokens = 0;
public:
    vector<Token> token_lis = token_list;
    Scanner(const string &input) : input(input) {};
    string stringer(){
        string filler = "\'";
        input = input.substr(1);
        //if (input.at(0)=='\'' && input.at(1) == '-')
        //figuring out the whole sitation with stringiing
        int starting = line;
        while (input.size()!= 1){
            filler += input[0];
            //cout << filler << endl;
            if (input.at(0) == '\''){
                if (input.at(1)=='\''){
                    filler += input[1];
                    input = input.substr(2);
                }
                else {input = input.substr(1);
                Token t = Token(STRING,filler,line);
                token_list.push_back(t);
                //if (input.at(0) == '\n') { line++; }
                //cout << "DEBUG: REDUCTION 1" << endl;
                //cout << input.at(0) << endl;
                //input = input.substr(1);
                return input;
                }
            }
            //cout << "DEBUG: REDUCTION 2" << endl;
            //cout << input.at(0) << endl;
            input = input.substr(1);
            if (input.at(0) == '\n') { line++; }
        }
        Token t = Token(UNDEFINED, filler, starting);
        token_list.push_back(t);
        return input;
    }
    void qouter(){
        string filler = "#";
        input = input.substr(1);
        if (input.at(0) == '|'){
            while (input.size()!=1){

                filler += input[0];
                if (input.at(0)=='\n'){line ++;}

                if(input.at(0) == '#' && input.at(1) == '|'){
                        filler += "#|";
                        Token t = Token(COMMENT,filler,line);
                        //token_list.push_back(t);
                        input = input.substr(2);
                        return;

                    }

                input = input.substr(1);
            }
            Token t = Token(UNDEFINED, filler, line);
            token_list.push_back(t);
            return;
        }
        //if (input.at(0)=='\'' && input.at(1) == '-')
        //figuring out the whole sitation with stringiing
        while (input.size()!= 1){

            //cout << filler << endl;
            if (input.at(0) == '\n'){
                Token t = Token(COMMENT,filler,line);
                //token_list.push_back(t);
                line ++;
                input = input.substr(1);
                //return input;
                return;
            }
            filler += input[0];
            input = input.substr(1);
        }
    }
    void scanToken() {
        line = 1;
        //cout << input << endl;
        //cout << input.size() << endl;
        if (input.size() == 0){Token t = Token(EO, "",line );
            //cout << "DEBUG: I MADE IT" << endl;
            token_list.push_back(t);
            return; }
        input += "0";
        //cout << input << endl;
        //line = 1;
        while (input.size() > 1) {
            //cout << "L oop is being done" <<endl;
            while (isspace(input.at(0))) {
                if (input.at(0) == '\n') { line++; }
                if(input.size() == 1){break;}
                input = input.substr(1);
                //cout << input << endl;

            }
            if (input.at(0) == ',') {
                Token t = Token(COMMA, ",", line);
                token_list.push_back(t);
                input = input.substr(1);
            }
            if (input.at(0) == '.') {
                Token t = Token(PERIOD, ".", line);
                token_list.push_back(t);
                input = input.substr(1);
            }
            if (input.at(0) == '?') {
                Token t = Token(Q_MARK, "?", line);
                token_list.push_back(t);
                input = input.substr(1);
            }
            if (input.at(0) == ':') {
                if (input.at(1) == '-') {
                    Token t = Token(COLON_DASH, ":-", line);
                    token_list.push_back(t);
                    input = input.substr(2);
                    continue;
                } else {
                    //cout << "COLON< SEX" << endl;
                    Token t = Token(COLON, ":", line);
                    token_list.push_back(t);
                    input = input.substr(1);
                    continue;
                }
            }
            if (input.at(0) == '(') {
                Token t = Token(LEFT_PAREN, "(", line);
                token_list.push_back(t);
                input = input.substr(1);
                continue;

            }
            if (input.at(0) == ')') {
                Token t = Token(RIGHT_PAREN, ")", line);
                token_list.push_back(t);
                input = input.substr(1);
                continue;
            }

            if (input.at(0) == '*') {
                Token t = Token(MUlTIPLY, "*", line);
                token_list.push_back(t);
                input = input.substr(1);
                continue;
            }
            if (input.at(0) == '+') {
                Token t = Token(ADD, "+", line);
                token_list.push_back(t);
                input = input.substr(1);
                continue;
            }
            if ((input.at(0) == 'S' && input.at(1) == 'c' && input.at(2) == 'h'&& input.at(3) == 'e'
                 && input.at(4) == 'm'&& input.at(5) == 'e'&& input.at(6) == 's') && ((input.at(7) == ':') | isspace(input.at(7)))
                    ) { // check for schemes
                input = input.substr(1);
                string inp = "S";
                for (int i = 0; i < 6; i++) {
                    inp += input[i];

                }
                if (inp == "Schemes"&& ((input.at(6) == ':' )| isspace(input.at(6)))) {
                    Token t = Token(SCHEMES, "Schemes", line);
                    token_list.push_back(t);
                }
                input = input.substr(6);
                if (isalpha(input.at(0))){
                    //cout << input[0] << endl;
                    string tem = inp;
                    //cout << tem << endl;
                    //input = input.substr(1);
                    while (isalnum(input.at(0))) {
                        if (input.size()==1){break;}
                        string que = string(1,input[0]);
                        tem += que;
                        //if (input.size()==1){break;}
                        input = input.substr(1);

                    }

                    Token t = Token(ID, tem, line);
                    //if (input.at(0) == '\n') { line++; }
                    token_list.push_back(t);

                    continue;

                }
                continue;
            }
            if ((input.at(0) == 'F' && input.at(1) == 'a' && input.at(2) == 'c'&& input.at(3) == 't'
                 && input.at(4) == 's') && ((input.at(5) == ':') | isspace(input.at(5)))
                    ) {
                input = input.substr(1);
                //input = input.substr(1);
                string inp = "F";

                for (int i = 0; i < 4; i++) {
                    inp += input[i];
                }
                if (inp == "Facts"&& ((input.at(4) == ':' )| isspace(input.at(4)))) {
                    Token t = Token(FACTS, "Facts", line);
                    token_list.push_back(t);
                }
                input = input.substr(4);
                if (isalpha(input.at(0))){
                    //cout << input[0] << endl;
                    string tem = inp;
                    //cout << tem << endl;
                    //input = input.substr(1);
                    while (isalnum(input.at(0))) {
                        if (input.size()==1){break;}
                        string que = string(1,input[0]);
                        tem += que;
                        //if (input.size()==1){break;}
                        input = input.substr(1);

                    }

                    Token t = Token(ID, tem, line);
                    //if (input.at(0) == '\n') { line++; }
                    token_list.push_back(t);

                    continue;

                }
                continue;
            }
            if ((input.at(0) == 'R' && input.at(1) == 'u' && input.at(2) == 'l'&& input.at(3) == 'e'
                 && input.at(4) == 's') && ((input.at(5) == ':') | isspace(input.at(5)))
                    ) {
                input = input.substr(1);
                //input = input.substr(1);
                string inp = "R";

                for (int i = 0; i < 4; i++) {
                    inp += input[i];
                }
                if (inp == "Rules" && ((input.at(4) == ':') | isspace(input.at(4)))) {
                    Token t = Token(RULES, "Rules", line);
                    token_list.push_back(t);
                }
                input = input.substr(4);
                if (isalpha(input.at(0))){
                    //cout << input[0] << endl;
                    string tem = inp;
                    //cout << tem << endl;
                    //input = input.substr(1);
                    while (isalnum(input.at(0))) {
                        if (input.size()==1){break;}
                        string que = string(1,input[0]);
                        tem += que;
                        //if (input.size()==1){break;}
                        input = input.substr(1);

                    }

                    Token t = Token(ID, tem, line);
                    //if (input.at(0) == '\n') { line++; }
                    token_list.push_back(t);

                    continue;

                }
                continue;
            }
            if ((input.at(0) == 'Q' && input.at(1) == 'u' && input.at(2) == 'e'&& input.at(3) == 'r'
            && input.at(4) == 'i'&& input.at(5) == 'e'&& input.at(6) == 's') && ((input.at(7) == ':') | isspace(input.at(7)))
            ) {
                //cout<< " DEBUG: I made it to the QUERIES DEBUG" << endl;
                input = input.substr(1);
                //input = input.substr(1);
                //cout << input.at(0,5) << endl;
                string inp = "Q";

                for (int i = 0; i < 6; i++) {
                    inp += input[i];
                    //cout << input[i] << endl;

                }
                //cout << " DEBUG: I made it through the inner loop" << endl;
                //cout << input << endl;
                if (inp == "Queries" && ((input.at(6) == ':')| isspace(input.at(6)))) {
                    //cout << "DEBUG: IT IS QUERIES" << endl;
                    Token t = Token(QUERIES, "Queries", line);
                    token_list.push_back(t);
                }
                //cout << " is not queries." << endl;
                input = input.substr(6);
                if (isalpha(input.at(0))){
                    //cout << input[0] << endl;
                    string tem = inp;
                    //cout << tem << endl;
                    //input = input.substr(1);
                    while (isalnum(input.at(0))) {
                        if (input.size()==1){break;}
                        string que = string(1,input[0]);
                        tem += que;
                        //if (input.size()==1){break;}
                        input = input.substr(1);

                    }

                    Token t = Token(ID, tem, line);
                    //if (input.at(0) == '\n') { line++; }
                    token_list.push_back(t);

                    continue;

                }
                //cout << input << endl;
                continue;
            }
            if (isalpha(input.at(0))){
                //cout << input[0] << endl;
                string tem = string(1,input[0]);
                //cout << tem << endl;
                input = input.substr(1);
                while (isalnum(input.at(0))) {
                    if (input.size()==1){break;}
                    string que = string(1,input[0]);
                    tem += que;
                    //if (input.size()==1){break;}
                    input = input.substr(1);

                }

                Token t = Token(ID, tem, line);
                //if (input.at(0) == '\n') { line++; }
                token_list.push_back(t);

                continue;

            }
            if (input.at(0) == '\''){
                input = stringer();
                continue;
            }
            if (input.at(0) == '#'){
                qouter();
                continue;
            }
            if (input.size()== 1){ break;}
            else if (!isspace(input.at(0))){
                //cout<< input[0] << endl;
                string j = string(1,input[0]);
                Token t = Token(UNDEFINED, j, line);
                token_list.push_back(t);
                input = input.substr(1);
            }
            //if (input.size()== 1){ break;}
        }
        Token t = Token(EO, "",line);
        token_list.push_back(t);
        token_lis = token_list;
    }
    //return token_list;
    void print_tokens() {
        vector<Token>::iterator itr;
        for (itr = token_list.begin(); itr != token_list.end(); itr++){
            cout<< itr->toString()<<endl;
        }
        cout << "Total Tokens = " << token_list.size() <<endl;
    };
};
