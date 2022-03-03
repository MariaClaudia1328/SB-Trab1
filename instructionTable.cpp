#ifndef INSTRUCTION_TABLE_H
#define INSTRUCTION_TABLE_H

using namespace std;

// A ideia aqui é montar a tabela de instruções 
// e receber o opcode da instrução da linha que 
// está sendo processada. A partir desse opcode, 
// retorno as informações que são necessárias para
// a montagem e análise do código

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <string>
#include <typeinfo>
#include <regex>
#include <sstream> 
using namespace std;

int infoInstructions(int opcode, int infoType){
    switch(opcode){
        case 9:
            if(infoType == 0)
                return 2;
            return 3;
            break;
        case 14:
            if(infoType == 0)
                return 0;
            return 1;
            break;
        default:
            if(infoType == 0)
                return 1;
            return 2;
            break;
    }

    return -1;
}

vector<vector<int>> createInstructionTable (){

    vector<vector<int>> opcodeInfo;

    for(int i = 0; i <= 1; i++){
        vector<int> opcodeOperator;
        vector<int> opcodeLenght;
        if(i == 0){
            for(int j = 0; j < 15; j++){
                int info = infoInstructions(j,i);
                opcodeOperator.push_back(info);
            }
            opcodeInfo.push_back(opcodeOperator);
        }if(i == 1){
            for(int j = 0; j < 15; j++){
                int info = infoInstructions(j,i);
                opcodeOperator.push_back(info);
            }
            opcodeInfo.push_back(opcodeOperator);
        }
    }

    return opcodeInfo;
}

vector<vector<int>> identifyInfoInstruction(vector<vector<int>> instructionTable, string opcode){
    vector<vector<int>> instructionInfo;
    int opcodeNumber;

    if( opcode == "add" || opcode == "ADD" ){
        opcodeNumber = 1;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "sub" || opcode == "SUB" ){
        opcodeNumber = 2;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "mult" || opcode == "MULT" ){
        opcodeNumber = 3;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "div" || opcode == "DIV" ){
        opcodeNumber = 4;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmp" || opcode == "JMP" ){
        opcodeNumber = 5;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmpn" || opcode == "JMPN" ){
        opcodeNumber = 6;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmpp" || opcode == "JMPP" ){
        opcodeNumber = 7;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmpz" || opcode == "JMPZ" ){
        opcodeNumber = 8;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "copy" || opcode == "COPY" ){
        opcodeNumber = 9;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "load" || opcode == "LOAD" ){
        opcodeNumber = 10;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "store"|| opcode == "STORE" ){
        opcodeNumber = 11;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "input"|| opcode == "INPUT" ){
        opcodeNumber = 12;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "output"|| opcode == "OUTPUT" ){
        opcodeNumber = 13;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "stop"|| opcode == "STOP" ){
        opcodeNumber = 14;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }else{
        instructionInfo.push_back({-1,-1,-1});

    }
    
    

    return instructionInfo;

    
}

vector<string> parse(string line){
    
    regex regexep("\\w+|-\\d+");
    smatch m;
    vector<string> parseLine;
    string aux;
    for(auto i : line){
        if(i == ';') break;
        aux.push_back(i);
    }
    while(regex_search(aux,m,regexep)){
        for(auto x:m){
            parseLine.push_back(x);            
        }

        aux = m.suffix().str();
    }    

    for(auto i: parseLine){
        cout << i << " ";
    }

    cout << endl;

    return parseLine;

}

#endif