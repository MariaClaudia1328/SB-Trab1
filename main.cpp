#include <stdio.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <regex>

#include "instructionTable.cpp"

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

    while (i < content.length())
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
    for (auto line : lineVector){

        vector<string> _parse = parse(line);

        if(param == "-o"){
            
        }else if(param == "-p"){
            
        }else if(param == "-m"){
            
        }else{
            cerr << "Error: parameter unknown" << endl;
            exit(1);
        }
    }
    
    

    inputFile.close();
    outputFile.close();


    return 0;
}