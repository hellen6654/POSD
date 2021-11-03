#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "terminal.h"

std::string GetInputStringFromFile(std::string fileName)
{
    std::string temp = "";
    std::ifstream inputFile;
    std::stringstream ss;
    inputFile.open(fileName);
    while (getline(inputFile, temp))
        ss << temp + " ";
    inputFile.close();
    return ss.str();
}

void SetOutputStringToFile(std::string filename, std::string result)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::trunc);
    outputFile << result;
    outputFile.close();
}

int main(int argc, char *argv[])
{
    if (argc == 5)
    {

        std::string input = GetInputStringFromFile(argv[1]);
        input += argv[3];
        input += " ";
        input += argv[4];
        Terminal terminal(input);
        SetOutputStringToFile(argv[2], terminal.showResult());
    }
    else
    {
        throw std::string("invalid input");
    }
    return 0;
}

