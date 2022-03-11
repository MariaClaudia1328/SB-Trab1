#ifndef INSTRUCTION_PROCESS
#define INSTRUCTION_PROCESS

using namespace std;

// A ideia aqui é montar a tabela de instruções 
// e receber o opcode da instrução da linha que 
// está sendo processada. A partir desse opcode, 
// retorno as informações que são necessárias para
// a montagem e análise do código

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <string>
#include <typeinfo>
#include <regex>
#include <sstream> 
#include <unordered_map>
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

vector<vector<int>> identifyInfoInstruction(string opcode){
    vector<vector<int>> instructionInfo;
    int opcodeNumber;

    vector<vector<int>> instructionTable = createInstructionTable();

    // talvez seja redundante!
    for_each(opcode.begin(), opcode.end(), [](char &c){
        c = ::tolower(c);
    });

    if( opcode == "add"){
        opcodeNumber = 1;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "sub"){
        opcodeNumber = 2;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "mult"){
        opcodeNumber = 3;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "div"){
        opcodeNumber = 4;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmp"){
        opcodeNumber = 5;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmpn"){
        opcodeNumber = 6;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmpp" ){
        opcodeNumber = 7;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "jmpz"){
        opcodeNumber = 8;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "copy"){
        opcodeNumber = 9;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "load"){
        opcodeNumber = 10;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "store"){
        opcodeNumber = 11;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "input"){
        opcodeNumber = 12;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "output"){
        opcodeNumber = 13;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }
    else if( opcode == "stop"){
        opcodeNumber = 14;
        instructionInfo.push_back({ opcodeNumber,
                                        instructionTable[0][opcodeNumber],
                                        instructionTable[1][opcodeNumber]});
    }else{
        instructionInfo.push_back({-1,-1,-1});

    }
    
    

    return instructionInfo;

    
}

vector<string> eliminateComment(vector<string> lineVector){
    string aux;
    string line_;
    vector<string> newLineVector;
    for(auto line : lineVector){
        line_ = line;
        for(auto i: line_){
            if(i == ';') {
                break;
            }
            aux.push_back(i);
        }

        newLineVector.push_back(aux);
        aux.clear();
    }

    return newLineVector;
}

string identifySymbol(string line){
    string symbolBefore;
    regex reSymbol("\\w+:");
    smatch m;
    string symbolInfo;

    while(regex_search(line,m,reSymbol)){
        for(auto x:m){
            symbolBefore = x;
        }

        line = m.suffix().str();
    }

    if(symbolBefore.length() != 0){

        regex reSimple ("\\w+");
        string symbolAfter;

        while(regex_search(symbolBefore,m,reSimple)){
            for(auto x:m){
                symbolAfter = x;
            }

            symbolBefore = m.suffix().str();
        }
 

        symbolInfo = symbolAfter;

        return symbolInfo;
    }else{
        symbolInfo = "undefined";
        return symbolInfo;
    }
}

vector<string> parse(string line){
    
    regex regexep("\\w+:|\\w+|-\\d+");
    smatch m;
    vector<string> parseLine;

    // separar os simbolos e rótulos de cada linha
    while(regex_search(line,m,regexep)){
        

        for(auto x:m){
            parseLine.push_back(x);            
        }

        line = m.suffix().str();
    }   

    return parseLine;

}

vector<string> corrections(vector<string> lineVector){
    vector<string> newLineVector;
    bool aux = false;
    vector<string> symbolAlone;    
    vector<string> line_;

    for(auto line : lineVector){
        
        line_ = parse(line);
    
        regex r ("\\w+:");
        smatch sm;
        int size=0;
        int tam=0;      

        for(auto i:line_){
            if(regex_match(i,sm,r)){
                size = sm.size();
            }
            tam++;
        }     

        if(size == 1 && tam == 1){
            symbolAlone.push_back(line_[0]);
            aux = true;
            continue;
        }

        if(aux){
            string newLine;
            line = symbolAlone[0] + " " + line;
            aux = false;
            symbolAlone.clear();
        }

        // padronizar tudo pra lowercase 
        vector<string> lineAfter;
        for_each(line.begin(), line.end(), [](char &c){
            c = ::tolower(c);
        });
        

        newLineVector.push_back(line);        

    }

    return newLineVector;
}

string nameSymbol(string line, regex regexep, smatch mExp){
    string nameSymbolBefore;
    while(regex_search(line,mExp,regexep)){
        for(auto x:mExp){
            nameSymbolBefore = x; 
        }

        line = mExp.suffix().str();
    } 

    string nameSymbolAfter;
    for(auto i:nameSymbolBefore){
        if(i != ':'){
            nameSymbolAfter.push_back(i);
        }
    }

    return nameSymbolAfter;
}

vector<string> macrosProcess(vector<string> lineVector){
    vector<string> newLineVector;
    bool macroContent = false;
    //bool haveEnd = false;
    vector<string> MDT;
    string macroName;
    vector<string> line_;

    regex rMacro("macro");
    smatch m;

    vector<string> outMACRO;
    for(auto line:lineVector){

        line_ = parse(line);

        int size=0;
        smatch sm;
        for(auto i:line_){
            if(regex_match(i,sm,rMacro)){
                size = sm.size();
            }
        }

        if(size == 1){          

            // pega nome da macro
            regex rMacroName("\\w+:");
            macroName = nameSymbol(line,rMacroName, m);

            // pega conteudo da macro
            macroContent = true;
            line = "";
        }

        // apitar erro caso nao tenha endmacro
        regex rEndMacro("endmacro");
        if(regex_search(line,m,rEndMacro)){
            macroContent = false;
            line = "";
            //haveEnd = true; // ve se tem endmacro
        }

        if(macroContent){
            MDT.push_back(line);
            line = "";
        }

        bool putContent = false;;
        for(auto i:line_){
            if(i == macroName){
                putContent = true;
            }
        } 

        if(putContent){
            string aux;
            for(auto i:MDT){
                outMACRO.push_back(i);
            }
            putContent = false;
        }else{
            outMACRO.push_back(line);
        }
    }

    for(auto line: outMACRO){
        if(line != ""){
            newLineVector.push_back(line);
        }
    }

    return newLineVector;
}

#endif