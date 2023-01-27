#pragma once
#include "Token.h"
#include "StateMachine.h"
#include <fstream>
#include <iostream>
// Included to use replace_if for removing whitespace
#include <algorithm>

class ScannerClass
{
public:
    ScannerClass(std::string &inputFileName);
    ~ScannerClass();
    TokenClass GetNextToken();

private:
    std::ifstream mFin;
};