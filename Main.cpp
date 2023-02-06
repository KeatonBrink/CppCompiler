#include "Scanner.h"
#include "Debug.h"
#include "Symbol.h"

void testScanner();

void testSymbolTable();

int main()
{
    std::cout << "Scanner test" << std::endl;
    testScanner();
    std::cout << "Symbol Table test" << std::endl;
    testSymbolTable();
    return 0;
}

void testScanner()
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
}

void testSymbolTable()
{
    SymbolTableClass mySymTab;
    mySymTab.AddEntry("x");
    mySymTab.AddEntry("y");
    mySymTab.SetValue("y", 12);
    std::cout << "y is " << mySymTab.GetValue("y") << std::endl;
    mySymTab.SetValue("y", 15);
    std::cout << "y is " << mySymTab.GetValue("y") << std::endl;
    std::cout << mySymTab.GetIndex("w") << std::endl;
    std::cout << (int)mySymTab.GetCount() << std::endl;

    // Test conditions
    // mySymTab.AddEntry("x");
    // mySymTab.GetValue("w");
    mySymTab.SetValue("a", 3);

    // Final test output if all works
    std::cout << "Made it through tests" << std::endl;
}