#include "Parser.h"
// I guess there is something wrong here
ParserClass::ParserClass(ScannerClass *so, SymbolTableClass *sto) : mScanner(so), mSymboltable(sto) {}

StartNode *ParserClass::Start()
{
    ProgramNode *pn = Program();
    Match(ENDFILE_TOKEN);
    StartNode *sn = new StartNode(pn);
    return sn;
}

ProgramNode *ParserClass::Program()
{
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode *bn = Block();
    ProgramNode *pn = new ProgramNode(bn);
    return pn;
}
BlockNode *ParserClass::Block()
{
    Match(LCURLY_TOKEN);
    StatementGroupNode *sgn = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode *bn = new BlockNode(sgn);
    return bn;
}
StatementGroupNode *ParserClass::StatementGroup()
{
    StatementGroupNode *sgn = new StatementGroupNode();
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    while (nextTok == INT_TOKEN || nextTok == IDENTIFIER_TOKEN || nextTok == COUT_TOKEN || nextTok == LCURLY_TOKEN)
    {
        if (nextTok == INT_TOKEN)
        {
            DeclarationStatementNode *dsn = DeclarationStatement();
            sgn->AddStatement(dsn);
        }
        else if (nextTok == IDENTIFIER_TOKEN)
        {
            AssignmentStatementNode *asn = AssignmentStatement();
            sgn->AddStatement(asn);
        }
        else if (nextTok == COUT_TOKEN)
        {
            CoutStatementNode *csn = CoutStatement();
            sgn->AddStatement(csn);
        }
        else if (nextTok == LCURLY_TOKEN)
        {
            BlockNode *bn = Block();
            sgn->AddStatement(bn);
        }
        nextTok = mScanner->PeekNextToken().GetTokenType();
    }
    return sgn;
}
DeclarationStatementNode *ParserClass::DeclarationStatement()
{
    Match(INT_TOKEN);
    IdentifierNode *in = Identifier();
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode *dsn = new DeclarationStatementNode(in);
    return dsn;
}
AssignmentStatementNode *ParserClass::AssignmentStatement()
{
    IdentifierNode *in = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode *en = Expression();
    Match(SEMICOLON_TOKEN);
    AssignmentStatementNode *asn = new AssignmentStatementNode(in, en);
    return asn;
}
CoutStatementNode *ParserClass::CoutStatement()
{
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode *en = Expression();
    Match(SEMICOLON_TOKEN);
    CoutStatementNode *csn = new CoutStatementNode(en);
    return csn;
}
ExpressionNode *ParserClass::Expression()
{
    return Relational();
}
ExpressionNode *ParserClass::Relational()
{
    ExpressionNode *current = PlusMinus();
    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == LESS_TOKEN)
    {
        Match(tt);
        current = new LessNode(current, PlusMinus());
    }
    else if (tt == LESSEQUAL_TOKEN)
    {
        Match(tt);
        current = new LessEqualNode(current, PlusMinus());
    }
    else if (tt == GREATER_TOKEN)
    {
        Match(tt);
        current = new GreaterNode(current, PlusMinus());
    }
    else if (tt == GREATEREQUAL_TOKEN)
    {
        Match(tt);
        current = new GreaterEqualNode(current, PlusMinus());
    }
    else if (tt == EQUAL_TOKEN)
    {
        Match(tt);
        current = new EqualNode(current, PlusMinus());
    }
    else if (tt == NOTEQUAL_TOKEN)
    {
        Match(tt);
        current = new NotEqualNode(current, PlusMinus());
    }
    return current;
}
ExpressionNode *ParserClass::PlusMinus()
{
    ExpressionNode *current = TimesDivide();
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    while (nextTok == PLUS_TOKEN || nextTok == MINUS_TOKEN)
    {
        Match(nextTok);
        if (nextTok == PLUS_TOKEN)
        {
            current = new PlusNode(current, TimesDivide());
        }
        else
        {
            current = new MinusNode(current, TimesDivide());
        }
        nextTok = mScanner->PeekNextToken().GetTokenType();
    }
    return current;
}

ExpressionNode *ParserClass::TimesDivide()
{
    ExpressionNode *current = Factor();
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    while (nextTok == TIMES_TOKEN || nextTok == DIVIDE_TOKEN)
    {
        Match(nextTok);
        if (nextTok == TIMES_TOKEN)
        {
            current = new TimesNode(current, TimesDivide());
        }
        else
        {
            current = new DivideNode(current, TimesDivide());
        }
        nextTok = mScanner->PeekNextToken().GetTokenType();
    }
    return current;
}

ExpressionNode *ParserClass::Factor()
{
    TokenType nextTok = mScanner->PeekNextToken().GetTokenType();
    if (nextTok == IDENTIFIER_TOKEN)
    {
        return Identifier();
    }
    else if (nextTok == INTEGER_TOKEN)
    {
        return Integer();
    }
    else if (nextTok == LPAREN_TOKEN)
    {
        Match(LPAREN_TOKEN);
        ExpressionNode *en = Expression();
        Match(RPAREN_TOKEN);
        return en;
    }
    else
    {
        std::cerr << "Error in ParserClass::Factor. " << std::endl;
        std::cerr << "Expected token type IDENTIFIER_TOKEN INTEGER_TOKEN or LPAREN_TOKEN, but got type "
                  << nextTok << std::endl;
        exit(1);
    }
}

IdentifierNode *ParserClass::Identifier()
{
    TokenClass tc = Match(IDENTIFIER_TOKEN);
    IdentifierNode *idn = new IdentifierNode(tc.GetLexeme(), mSymboltable);
    return idn;
}
IntegerNode *ParserClass::Integer()
{
    TokenClass tc = Match(INTEGER_TOKEN);
    IntegerNode *inn = new IntegerNode(atoi(tc.GetLexeme().c_str()));
    return inn;
}

TokenClass ParserClass::Match(TokenType expectedType)
{
    TokenClass currentToken = mScanner->GetNextToken();
    MSG(currentToken);
    if (currentToken.GetTokenType() != expectedType)
    {
        std::cerr << "Error in ParserClass::Match. " << std::endl;
        std::cerr << "Expected token type " << TokenClass::GetTokenTypeName(expectedType) << ", but got type " << currentToken.GetTokenTypeName() << std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() << ". Lexeme: \"" << currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}