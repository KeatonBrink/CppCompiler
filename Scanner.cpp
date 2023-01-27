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
        // if (c != ' ' && c != '\n' && c != '\t')
        myLexeme.push_back(c);
    } while (curMachineState != CANTMOVE_STATE);
    myLexeme.pop_back();
    // Not sure how this works, but it removes white space.
    myLexeme.erase(remove_if(myLexeme.begin(), myLexeme.end(), isspace), myLexeme.end());
    mFin.unget();
    TokenClass curToken(curTokenType, myLexeme);
    curToken.CheckReserved();
    if (curTokenType == BAD_TOKEN)
        std::cout << "That is a bad token: " << myLexeme << std::endl;
    return curToken;
}