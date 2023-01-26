#include "Scanner.h"

ScannerClass::ScannerClass(std::string &inputFileName)
{
    mFin.open(inputFileName.c_str(), std::ios::binary);
    if (!mFin)
    {
        std::cout << "error opening file" << std::endl;
    }
}

ScannerClass::~ScannerClass()
{
    mFin.close();
}

TokenClass ScannerClass::GetNextToken()
{
    StateMachineClass stateMachine;
    MachineState curMachineState = START_STATE;
    TokenType curTokenType;
    char c;
    std::string myLexeme = "";
    do
    {
        c = mFin.get();
        curMachineState = stateMachine.UpdateState(c, curTokenType);
        myLexeme.push_back(c);
    } while (curMachineState != CANTMOVE_STATE);
    myLexeme.pop_back();
    mFin.unget();
    TokenClass curToken(curTokenType, myLexeme);
    curToken.CheckReserved();
    if (curTokenType == BAD_TOKEN)
        std::cout << "That is a bad token: " << myLexeme << std::endl;
    return curToken;
}