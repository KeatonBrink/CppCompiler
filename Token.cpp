#include "Token.h"

TokenClass::TokenClass()
{
    mType = BAD_TOKEN;
    mLexeme = "None";
}

TokenClass::TokenClass(TokenType type, const std::string &lexeme)
{
    mType = type;
    mLexeme = lexeme;
}

void TokenClass::CheckReserved()
{
    std::string myString = mLexeme;
    std::locale loc;
    for (std::string::size_type i = 0; i < myString.length(); ++i)
        myString[i] = std::toupper(myString[i], loc);
    if (myString.length() == 3 && myString == "INT")
    {
        mType = INT_TOKEN;
    }
    else if (myString.length() == 4)
    {
        if (myString == "VOID")
        {
            mType = VOID_TOKEN;
        }
        else if (myString == "MAIN")
        {
            mType = MAIN_TOKEN;
        }
        else if (myString == "COUT")
        {
            mType = COUT_TOKEN;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const TokenClass &tc)
{
    out << tc.GetTokenTypeName() << " " << tc.GetLexeme();
    return out;
}