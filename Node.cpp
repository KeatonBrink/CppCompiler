#include "Node.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode *pProgramNode) : mProgramNode(pProgramNode) { MSG("Making StartNode"); }
StartNode::~StartNode()
{
    MSG("Deleting Start Node");
    delete mProgramNode;
}

ProgramNode::ProgramNode(BlockNode *pBlockNode) : mBlockNode(pBlockNode) { MSG("Making Program Node"); }
ProgramNode::~ProgramNode()
{
    MSG("Deleting Program Node");
    delete mBlockNode;
}

BlockNode::BlockNode(StatementGroupNode *pStatementGroupNode) : mStatementGroupNode(pStatementGroupNode) { MSG("Making Block Node"); }
BlockNode::~BlockNode()
{
    MSG("Deleting Block Node");
    delete mStatementGroupNode;
}

void StatementGroupNode::AddStatement(StatementNode *pStatementNode) { mStatementNodes.push_back(pStatementNode); }
StatementGroupNode::~StatementGroupNode()
{
    MSG("Deleting StatementGroupNode");
    for (int i = 0; i < (int)mStatementNodes.size(); i++)
    {
        delete mStatementNodes[i];
    }
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *pIdentifierNode) : mIdentifierNode(pIdentifierNode) { MSG("Making Declaration Statement Node"); }
DeclarationStatementNode::~DeclarationStatementNode()
{
    MSG("Deleting Declaration Statement Node");
    delete mIdentifierNode;
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *pIdentifierNode, ExpressionNode *pExpressionNode) : mIdentifierNode(pIdentifierNode), mExpressionNode(pExpressionNode) { MSG("Making assignment Statement Node"); }
AssignmentStatementNode::~AssignmentStatementNode()
{
    MSG("Deleting Assignment Statement Node");
    delete mIdentifierNode;
    delete mExpressionNode;
}

CoutStatementNode::CoutStatementNode(ExpressionNode *pExpressionNode) : mExpressionNode(pExpressionNode) { MSG("Making Cout Statement Node"); }
CoutStatementNode::~CoutStatementNode()
{
    MSG("Deleting Cout Statement Node");
    delete mExpressionNode;
}

ExpressionNode::~ExpressionNode() {}

IntegerNode::IntegerNode(int aInt) : mInt(aInt) { MSG("Making Integer Node"); }
IntegerNode::~IntegerNode() { MSG("Deleting Integer Node"); }
int IntegerNode::Evaluate() { return mInt; }

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass *pSymbolTable) : mLabel(label), mSymbolTable(pSymbolTable) { MSG("Making Identifier Node"); }
IdentifierNode::~IdentifierNode() { MSG("Deleting Identifier Node"); }

void IdentifierNode::DeclareVariable()
{
    mSymbolTable->AddEntry(mLabel);
}
void IdentifierNode::SetValue(int v)
{
    mSymbolTable->SetValue(mLabel, v);
}
int IdentifierNode::GetIndex()
{
    return mSymbolTable->GetIndex(mLabel);
}
int IdentifierNode::Evaluate()
{
    return mSymbolTable->GetValue(mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *ExpressionNode1, ExpressionNode *ExpressionNode2) : mLeftPENode(ExpressionNode1), mRightPENode(ExpressionNode2)
{
    MSG("Making Binary Operation Node");
}

BinaryOperatorNode::~BinaryOperatorNode()
{
    MSG("Deleting Binary Operator Node");
    delete mLeftPENode;
    delete mRightPENode;
}

PlusNode::PlusNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making PlusNode");
}

int PlusNode::Evaluate()
{
    return mLeftPENode->Evaluate() + mRightPENode->Evaluate();
}

MinusNode::MinusNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making MinusNode");
}

int MinusNode::Evaluate()
{
    return mLeftPENode->Evaluate() - mRightPENode->Evaluate();
}

TimesNode::TimesNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making TimesNode");
}

int TimesNode::Evaluate()
{
    return mLeftPENode->Evaluate() * mRightPENode->Evaluate();
}

DivideNode::DivideNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making DivideNode");
}

int DivideNode::Evaluate()
{
    return mLeftPENode->Evaluate() / mRightPENode->Evaluate();
}

LessNode::LessNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making LessNode");
}

int LessNode::Evaluate()
{
    if (mLeftPENode->Evaluate() < mRightPENode->Evaluate())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

LessEqualNode::LessEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making LessEqualNode");
}

int LessEqualNode::Evaluate()
{
    if (mLeftPENode->Evaluate() <= mRightPENode->Evaluate())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

GreaterNode::GreaterNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making GreaterNode");
}

int GreaterNode::Evaluate()
{
    if (mLeftPENode->Evaluate() > mRightPENode->Evaluate())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making GreaterEqualNode");
}

int GreaterEqualNode::Evaluate()
{
    if (mLeftPENode->Evaluate() >= mRightPENode->Evaluate())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

EqualNode::EqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making EqualNode");
}

int EqualNode::Evaluate()
{
    if (mLeftPENode->Evaluate() == mRightPENode->Evaluate())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

NotEqualNode::NotEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right)
{
    MSG("Making NotEqualNode");
}

int NotEqualNode::Evaluate()
{
    if (mLeftPENode->Evaluate() != mRightPENode->Evaluate())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}