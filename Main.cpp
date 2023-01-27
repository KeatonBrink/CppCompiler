#include "Scanner.h"

int main()
{
    std::string myCodeName = "P1Code.txt";
    ScannerClass scanner(myCodeName);
    TokenClass curTok;
    for (bool continueRead = true; continueRead;)
    {
        curTok = scanner.GetNextToken();
        std::cout << curTok << std::endl;
        if (curTok.GetTokenType() == ENDFILE_TOKEN)
        {
            continueRead = false;
        }
    }
    return 0;
}