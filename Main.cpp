#include "Scanner.h"
#include "Debug.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"

void testScanner();

void testSymbolTable();

void testNodes();

void testParserWithNoOutput();

int main()
{
    // std::cout << "Scanner test" << std::endl;
    // testScanner();
    // std::cout << "Symbol Table test" << std::endl;
    // testSymbolTable();
    // testNodes();
    testParserWithNoOutput();
    return 0;
}

void testNodes()
{
    SymbolTableClass symbols;

    IdentifierNode *id1 = new IdentifierNode("sum", &symbols);
    DeclarationStatementNode *dsn = new DeclarationStatementNode(id1);

    IdentifierNode *id2 = new IdentifierNode("plus", &symbols);
    IntegerNode *in1 = new IntegerNode(35);
    IntegerNode *in2 = new IntegerNode(400);
    PlusNode *plus = new PlusNode(in1, in2);
    AssignmentStatementNode *asn = new AssignmentStatementNode(id2, plus);

    IdentifierNode *id3 = new IdentifierNode("cout", &symbols);
    CoutStatementNode *csn = new CoutStatementNode(id3);

    StatementGroupNode *sgn = new StatementGroupNode;
    sgn->AddStatement(dsn);
    sgn->AddStatement(asn);
    sgn->AddStatement(csn);

    BlockNode *bn = new BlockNode(sgn);

    ProgramNode *pn = new ProgramNode(bn);

    StartNode *sn = new StartNode(pn);

    delete sn;
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

void testParserWithNoOutput()
{
    std::string filename = "validCode.txt";
    ScannerClass myScanner(filename);
    SymbolTableClass mySymbolTable;
    ParserClass myParser(&myScanner, &mySymbolTable);
    myParser.Start();
}