#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <regex>

#include "instructionProcess.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    auto inputFileName = argv[2];
    ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile)
    {
        cerr << "Error:input file could not be opened" << endl;
        exit(1);
    }
    auto outputFileName = argv[3];
    ofstream outputFile;
    outputFile.open(outputFileName);
    if (!outputFile)
    {
        cerr << "Error: output file could not be opened" << endl;
        exit(1);
    }

    string content((std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));

    int i = 0;
    string line;
    vector<string> lineVector;
    bool added = true;
    int lenght = content.length();
    while (i < lenght)
    {
        outputFile << content[i];

        if (content[i] != '\n')
        {
            added = false;
            line += content[i];
        }
        else if(content[i] == '\n')
        {
            added = true;
            if( line.length() != 0){ 
                lineVector.push_back(line);
            }
            line.clear();
        }
        i++;
    }

    if(!added)
        lineVector.push_back(line);

    // começar analise de linha por linha aqui
    string param = argv[1];

    // correção de espaços entre linhas
    lineVector = corrections(lineVector);

    // eliminar comentarios
    lineVector = eliminateComment(lineVector);

    //processamento de macros
    lineVector = macrosProcess(lineVector);

    //processamento das diretivas EQU e IF - fazer amanha

    // retirar os rotulos do codigo
    vector<string> newLineVector;
    for(auto line: lineVector){
        regex exp("^\\w+: |^\\w+:");
        string newLine;
        newLine = regex_replace(line,exp,"$1");
        
        newLineVector.push_back(newLine);
    }

    // processamento do valor das linhas
    vector<int> countLines;
    int aux = 0;
    for(auto line: newLineVector){
        
        countLines.push_back(aux);
        
        vector<string> line_;
        line_ = parse(line);

        for(auto item:line_){
            if(item == "const"){
                continue;
            }
            aux++;
        }
    }

    //primeira passagem --> arrumar valores
    unordered_map<string,int> symbolTable;
    int numberLine = 0;
    for(auto line:lineVector){
        string nameSymbol = identifySymbol(line);
        
        if(nameSymbol != "undefined"){
            symbolTable[nameSymbol] = countLines[numberLine];
        }

        numberLine++;
    }

    lineVector = newLineVector; // codigo sem rotulos

    /* for(auto i:symbolTable){
        cout << i.first << " " << i.second << endl;
    } */

    // segunda passagem

    // subtituindo symbol (rotulo é label em ingles)
    vector<string> parseLine;
    string newLine;
    int valueSymbol = 0;
    for (auto line : lineVector){
        parseLine = parse(line);

        vector<string> newparseLine;
        for(auto i : parseLine){            
            if(symbolTable.find(i) != symbolTable.end() ){
                i = to_string(symbolTable[i]);
                newparseLine.push_back(i);
                continue;
            }
            newparseLine.push_back(i);
        }

        // vector<vector<int>> identifyInfoInstruction(string opcode)
        int opcode = 0;
        vector<vector<int>> info;
        for(auto i:newparseLine){
            info = identifyInfoInstruction(i);
            
            
        }
        
    }


    if(param == "-o"){
            
    }else if(param == "-p"){
        
    }else if(param == "-m"){
        
    }else{
        cerr << "Error: parameter unknown" << endl;
        exit(1);
    }

    inputFile.close();
    outputFile.close();


    return 0;
}