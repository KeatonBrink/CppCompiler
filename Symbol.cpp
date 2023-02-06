#include "Symbol.h"

// returns true if <s> is already in the symbol table.
bool SymbolTableClass::Exists(const std::string &s)
{
    for (int i = 0; i < (int)mVariables.size(); i++)
    {
        if (mVariables[i].mLabel == s)
        {
            return true;
        }
    }
    return false;
}

// adds <s> to the symbol table,
// or quits if it was already there
void SymbolTableClass::AddEntry(const std::string &s)
{
    if (Exists(s))
    {
        std::cout << s << "  Already exists in Symbol Table" << std::endl;
        std::exit(1);
    }
    Variable temp = {
        s,
        0};
    mVariables.push_back(temp);
}

// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
int SymbolTableClass::GetValue(const std::string &s)
{
    for (int i = 0; i < (int)mVariables.size(); i++)
    {
        if (mVariables[i].mLabel == s)
        {
            return mVariables[i].mValue;
        }
    }
    std::cout << s << "  does not exist in Symbol Table" << std::endl;
    std::exit(1);
}

// sets variable <s> to the given value when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTableClass::SetValue(const std::string &s, int v)
{
    if (Exists(s))
    {
        mVariables[GetIndex(s)].mValue = v;
    }
    else
    {
        std::cout << s << "  does not exist in Symbol Table" << std::endl;
        std::exit(1);
    }
}

// returns a unique index of where variable <s> is.
// returns -1 if variable <s> is not there.
// Currently implemented with O(2n), as I am too lazy to fix it
int SymbolTableClass::GetIndex(const std::string &s)
{
    if (Exists(s))
    {
        for (int i = 0; i < (int)mVariables.size(); i++)
        {
            if (mVariables[i].mLabel == s)
            {
                return i;
            }
        }
    }
    return -1;
}

// returns the current number of variables in the symbol
// table.
size_t SymbolTableClass::GetCount()
{
    return mVariables.size();
}