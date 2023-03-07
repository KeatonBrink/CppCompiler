#include "Scanner.h"

ScannerClass::ScannerClass(std::string &inputFileName)
{
    mFin.open(inputFileName.c_str(), std::ios::binary);
    if (!mFin)
    {
        std::cout << "error opening file" << std::endl;
        std::exit(1);
    }
    mLineNumber = 1;
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
        if (c == '\n')
            mLineNumber++;
        if (curMachineState == START_STATE || curMachineState == EOF_STATE)
        {
            myLexeme = "";
        }
    } while (curMachineState != CANTMOVE_STATE);
    myLexeme.pop_back();
    // Not sure how this works, but it removes white space.
    // myLexeme.erase(remove_if(myLexeme.begin(), myLexeme.end(), isspace), myLexeme.end());
    if (c == '\n')
        mLineNumber--;
    mFin.unget();
    TokenClass curToken(curTokenType, myLexeme);
    curToken.CheckReserved();
    if (curTokenType == BAD_TOKEN)
    {
        std::cout << "That is a bad token: " << myLexeme << std::endl;
        std::exit(1);
    }
    // MSG(curToken);
    return curToken;
}

TokenClass ScannerClass::PeekNextToken()
{
    int preservedPos = mFin.tellg();
    int preservedLine = GetLineNumber();
    TokenClass retToken = GetNextToken();
    if (!mFin)        // if we triggered EOF, then seekg doesn't work,
        mFin.clear(); // unless we first clear()
    mFin.seekg(preservedPos);
    mLineNumber = preservedLine;
    return retToken;
}
