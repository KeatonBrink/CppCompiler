#pragma once

#include <vector>
#include <string>
#include "Symbol.h"
#include "Debug.h"

class Node;
class StartNode;
class ProgramNode;
class StatementGroupNode;
class StatementNode;
class BlockNode;
class DeclarationStatementNode;
class IdentifierNode;
class AssignmentStatementNode;
class ExpressionNode;
class IntegerNode;
class CoutStatementNode;

class Node
{
public:
    virtual ~Node();
};

class StartNode : public Node
{
public:
    StartNode(ProgramNode *pProgramNode);
    ~StartNode();

private:
    ProgramNode *mProgramNode;
};

class ProgramNode : public Node
{
public:
    ProgramNode(BlockNode *pBlockNode);
    ~ProgramNode();

private:
    BlockNode *mBlockNode;
};

class StatementNode : public Node
{
};
class BlockNode : public StatementNode
{
public:
    BlockNode(StatementGroupNode *pStatementGroupNode);
    ~BlockNode();

private:
    StatementGroupNode *mStatementGroupNode;
};

class StatementGroupNode : public Node
{
public:
    ~StatementGroupNode();
    void AddStatement(StatementNode *pStatementNode);

private:
    std::vector<StatementNode *> mStatementNodes;
};

class DeclarationStatementNode : public StatementNode
{
public:
    DeclarationStatementNode(IdentifierNode *pIdentifierNode);
    ~DeclarationStatementNode();

private:
    IdentifierNode *mIdentifierNode;
};

class AssignmentStatementNode : public StatementNode
{
public:
    AssignmentStatementNode(IdentifierNode *pIdentifierNode, ExpressionNode *pExpressionNode);
    ~AssignmentStatementNode();

private:
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;
};

class CoutStatementNode : public StatementNode
{
public:
    CoutStatementNode(ExpressionNode *pExpressionNode);
    ~CoutStatementNode();

private:
    ExpressionNode *mExpressionNode;
};

// Items below line need to be defined in Node.cpp
class ExpressionNode
{
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
};

class IntegerNode : public ExpressionNode
{
public:
    IntegerNode(int aInt);
    ~IntegerNode();
    int Evaluate();

private:
    int mInt;
};

class IdentifierNode : public ExpressionNode
{
public:
    IdentifierNode(std::string label, SymbolTableClass *pSymbolTable);
    ~IdentifierNode();
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();

private:
    std::string mLabel;
    SymbolTableClass *mSymbolTable;
};

class BinaryOperatorNode : public ExpressionNode
{
public:
    BinaryOperatorNode(ExpressionNode *ExpressionNode1, ExpressionNode *ExpressionNode2);
    virtual ~BinaryOperatorNode();

protected:
    ExpressionNode *mLeftPENode;
    ExpressionNode *mRightPENode;
};

class PlusNode : public BinaryOperatorNode
{
public:
    PlusNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class MinusNode : public BinaryOperatorNode
{
public:
    MinusNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class TimesNode : public BinaryOperatorNode
{
public:
    TimesNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class DivideNode : public BinaryOperatorNode
{
public:
    DivideNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class LessNode : public BinaryOperatorNode
{
public:
    LessNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class LessEqualNode : public BinaryOperatorNode
{
public:
    LessEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class GreaterNode : public BinaryOperatorNode
{
public:
    GreaterNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class GreaterEqualNode : public BinaryOperatorNode
{
public:
    GreaterEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class EqualNode : public BinaryOperatorNode
{
public:
    EqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};

class NotEqualNode : public BinaryOperatorNode
{
public:
    NotEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
};