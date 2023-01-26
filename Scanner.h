#pragma once
#include "Token.h"
#include "StateMachine.h"
#include <fstream>
#include <iostream>

class ScannerClass
{
public:
    ScannerClass(std::string &inputFileName);
    ~ScannerClass();
    TokenClass GetNextToken();

private:
    std::ifstream mFin;
};