#pragma once

#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"

class ParserClass
{
public:
    ParserClass(ScannerClass *so, SymbolTableClass *sto);
    StartNode *Start();

private:
    ProgramNode *Program();
    BlockNode *Block();
    StatementGroupNode *StatementGroup();
    DeclarationStatementNode *DeclarationStatement();
    AssignmentStatementNode *AssignmentStatement();
    CoutStatementNode *CoutStatement();
    ExpressionNode *Expression();
    ExpressionNode *Relational();
    ExpressionNode *PlusMinus();
    // I now see how the tails in the textbooka are intended to be
    // an extension of the base function.  I did not do this, and
    // I may have to revisit it sometime
    ExpressionNode *TimesDivide();
    ExpressionNode *Factor();
    IdentifierNode *Identifier();
    IntegerNode *Integer();

    TokenClass Match(TokenType matchTok);

    ScannerClass *mScanner;
    SymbolTableClass *mSymboltable;
};