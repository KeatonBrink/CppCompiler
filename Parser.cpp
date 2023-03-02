#include "Parser.h"
// I guess there is something wrong here
ParserClass::ParserClass(ScannerClass *so, SymbolTableClass *sto) : mScanner(so), mSymboltable(sto) {}

void ParserClass::Start()
{
    Program();
    Match(ENDFILE_TOKEN);
}

void ParserClass::Program()
{
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    Block();
}
void ParserClass::Block()
{
    Match(LCURLY_TOKEN);
    StatementGroup();
    Match(RCURLY_TOKEN);
}
void ParserClass::StatementGroup()
{
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    while (nextTok == INT_TOKEN || nextTok == IDENTIFIER_TOKEN || nextTok == COUT_TOKEN || nextTok == LCURLY_TOKEN)
    {
        if (nextTok == INT_TOKEN)
        {
            DeclarationStatement();
        }
        else if (nextTok == IDENTIFIER_TOKEN)
        {
            AssignmentStatement();
        }
        else if (nextTok == COUT_TOKEN)
        {
            CoutStatement();
        }
        else if (nextTok == LCURLY_TOKEN)
        {
            Block();
        }
        nextTok = mScanner->PeekNextToken().GetTokenType();
    }
}
void ParserClass::DeclarationStatement()
{
    Match(INT_TOKEN);
    Identifier();
    Match(SEMICOLON_TOKEN);
}
void ParserClass::AssignmentStatement()
{
    Identifier();
    Match(ASSIGNMENT_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}
void ParserClass::CoutStatement()
{
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}
void ParserClass::Expression()
{
    Relational();
}
void ParserClass::Relational()
{
    PlusMinus();
    RelationalTail();
}
void ParserClass::PlusMinus()
{
    TimesDivide();
    PlusMinusTail();
}
void ParserClass::RelationalTail()
{
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    if (nextTok == LESS_TOKEN)
    {
        Match(LESS_TOKEN);
        PlusMinus();
    }
    else if (nextTok == LESSEQUAL_TOKEN)
    {
        Match(LESSEQUAL_TOKEN);
        PlusMinus();
    }
    else if (nextTok == GREATER_TOKEN)
    {
        Match(GREATER_TOKEN);
        PlusMinus();
    }
    else if (nextTok == GREATEREQUAL_TOKEN)
    {
        Match(GREATEREQUAL_TOKEN);
        PlusMinus();
    }
    else if (nextTok == EQUAL_TOKEN)
    {
        Match(EQUAL_TOKEN);
        PlusMinus();
    }
    else if (nextTok == NOTEQUAL_TOKEN)
    {
        Match(NOTEQUAL_TOKEN);
        PlusMinus();
    }
}
void ParserClass::TimesDivide()
{
    Factor();
    TimesDivideTail();
}
void ParserClass::PlusMinusTail()
{
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    while (nextTok == PLUS_TOKEN || nextTok == MINUS_TOKEN)
    {
        Match(nextTok);
        TimesDivide();
        nextTok = mScanner->PeekNextToken().GetTokenType();
    }
}
void ParserClass::Factor()
{
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    if (nextTok == IDENTIFIER_TOKEN)
    {
        Identifier();
    }
    else if (nextTok == INTEGER_TOKEN)
    {
        Integer();
    }
    else if (nextTok == LPAREN_TOKEN)
    {
        Match(LPAREN_TOKEN);
        Expression();
        Match(RPAREN_TOKEN);
    }
    else
    {
        std::cerr << "Error in ParserClass::Factor. " << std::endl;
        std::cerr << "Expected token type IDENTIFIER_TOKEN INTEGER_TOKEN or LPAREN_TOKEN, but got type "
                  << nextTok << std::endl;
        exit(1);
    }
}
void ParserClass::TimesDivideTail()
{
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    while (nextTok == TIMES_TOKEN || nextTok == DIVIDE_TOKEN)
    {
        Match(nextTok);
        TimesDivide();
        nextTok = mScanner->PeekNextToken().GetTokenType();
    }
}
void ParserClass::Identifier() { Match(IDENTIFIER_TOKEN); }
void ParserClass::Integer() { Match(INTEGER_TOKEN); }

TokenClass ParserClass::Match(TokenType expectedType)
{
    TokenClass currentToken = mScanner->GetNextToken();
    if (currentToken.GetTokenType() != expectedType)
    {
        std::cerr << "Error in ParserClass::Match. " << std::endl;
        std::cerr << "Expected token type " << TokenClass::GetTokenTypeName(expectedType) << ", but got type " << currentToken.GetTokenTypeName() << std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() << ". Lexeme: \"" << currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}