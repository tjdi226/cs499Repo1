#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "grammar.h"
#include <bits/stdc++.h>

using namespace std;

  //-----------------------------------------------------------------------------------
  //                                 startup
  //-----------------------------------------------------------------------------------
bool parser::startup(string fn){
    //--------------------
    ifstream file;
    string fileName, line;
    int check;
    int cnt = 0;
    bool test;
    //-------------------
    check = scan.open(fn);
    if (check == 1){
        cout << "file opens." << endl;
        test = true;
        
    }
    if (check == 0){
        cout << "file not opening." << endl;
        test = false;
        cout << "Enter file name: ";
        getline(cin,fileName);
        compile(fileName);
    }
    return test;   
}
  //-----------------------------------------------------------------------------------
  //                                 selectProd
  //----------------------------------------------------------------------------------
int parser::selectProd(token lhs){
    int count = 1;
    for(int i=0; i < GR_NUMPRODS; i++){
        for(int j= GR_FIRST_SELSET; j< GR_LAST_SELSET; j++){
            if(PROD[i][j] == lhs.getId()){
                return i;
            }
        }
    }
    //return i;
    return count;
}

bool parser::isNonTerminal(token t){
    cout << "TEST: ";
    cout << t.getPrintString();
       
}

  //-----------------------------------------------------------------------------------
  //                                 compile
  //----------------------------------------------------------------------------------
string parser::compile(string fn){
    bool err;
    token t;
    err = startup(fn);
    //-----------------------------
    t = scan.getNextToken();
    isNonTerminal(t);
    tokStack.push(t);
    while(!scan.isError() && !tokStack.empty() && t.getId() != TOK_EOS){
        t = scan.getNextToken();
        isNonTerminal(t);        

    }
    if(scan.isError()){
        cout << scan.getError() << endl;
    }
    cout << endl;
    if(err == true){
        return "No production found\n";
    }
    else{
        return "";
    }
}