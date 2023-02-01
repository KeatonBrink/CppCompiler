#include "Scanner.h"
#include "Debug.h"

int main()
{
    std::string myCodeName = "P1Code.txt";
    ScannerClass scanner(myCodeName);
    TokenClass curTok;
    MSG("hello")
    for (bool continueRead = true; continueRead;)
    {
        curTok = scanner.GetNextToken();
        std::cout << " Line Number: " << scanner.GetLineNumber() << ", " << curTok << std::endl;
        if (curTok.GetTokenType() == ENDFILE_TOKEN)
        {
            continueRead = false;
        }
    }
    return 0;
}