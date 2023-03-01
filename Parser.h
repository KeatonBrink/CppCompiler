#pragma once

#include "Scanner.h"
#include "Symbol.h"

class ParserClass
{
public:
    ParserClass(ScannerClass *so, SymbolTableClass *sto);
    void Start();

private:
    void Program();
    void Block();
    void StatementGroup();
    void DeclarationStatement();
    void AssignmentStatement();
    void CoutStatement();
    void Expression();
    void Relational();
    void PlusMinus();
    // I now see how the tails in the textbooka are intended to be
    // an extension of the base function.  I did not do this, and
    // I may have to revisit it sometime
    void RelationalTail();
    void TimesDivide();
    void PlusMinusTail();
    void Factor();
    void TimesDivideTail();
    void Identifier();
    void Integer();

    TokenClass Match(TokenType matchTok);

    ScannerClass *mScanner;
    SymbolTableClass *mSymboltable;
};