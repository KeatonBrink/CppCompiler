#include "StateMachine.h"

StateMachineClass::StateMachineClass()
{
    mCurrentState = START_STATE;

    // Initialize mLegalMoves
    for (int curState = 0; curState < LAST_STATE; curState++)
    {
        for (int curChar = 0; curChar < LAST_CHAR; curChar++)
        {
            mLegalMoves[curState][curChar] = CANTMOVE_STATE;
        }
    }
    // ******How do I handle "!"?
    // STARTSTATE
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][RETURN_CHAR] = START_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
    mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
    mLegalMoves[START_STATE][SCOLON_CHAR] = SCOLON_STATE;
    mLegalMoves[START_STATE][LTHAN_CHAR] = LTHAN_STATE;
    mLegalMoves[START_STATE][GTHAN_CHAR] = GTHAN_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
    mLegalMoves[START_STATE][ASSIGNMENT_CHAR] = ASSIGNMENT_STATE;
    mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE;

    // IDENTIFIER_STATE
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;

    // INTEGER_STATE
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;

    // LTHAN_STATE
    mLegalMoves[LTHAN_STATE][LTHAN_CHAR] = INSERTION_STATE;
    mLegalMoves[LTHAN_STATE][ASSIGNMENT_CHAR] = LEQUAL_STATE;

    // GTHAN_STATE
    mLegalMoves[GTHAN_STATE][ASSIGNMENT_CHAR] = GEQUAL_STATE;

    // NOT_STATE
    mLegalMoves[NOT_STATE][ASSIGNMENT_CHAR] = NEQUAL_STATE;

    // ASSIGNMENT_STATE
    mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = EQUAL_STATE;

    // DIVIDE_STATE
    mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENT_STATE;
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;

    // BLOCKCOMMENT_STATE
    for (int curChar = 0; curChar < LAST_CHAR; curChar++)
    {
        mLegalMoves[BLOCKCOMMENT_STATE][curChar] = BLOCKCOMMENT_STATE;
    }
    mLegalMoves[BLOCKCOMMENT_STATE][TIMES_CHAR] = EBLOCKCOMMENT_STATE;

    // EBLOCKCOMMENT_STATE
    for (int curChar = 0; curChar < LAST_CHAR; curChar++)
    {
        mLegalMoves[EBLOCKCOMMENT_STATE][curChar] = BLOCKCOMMENT_STATE;
    }
    mLegalMoves[EBLOCKCOMMENT_STATE][TIMES_CHAR] = EBLOCKCOMMENT_STATE;
    mLegalMoves[EBLOCKCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;

    // LINECOMMENT_STATE
    for (int curChar = 0; curChar < LAST_CHAR; curChar++)
    {
        mLegalMoves[LINECOMMENT_STATE][curChar] = LINECOMMENT_STATE;
    }
    mLegalMoves[LINECOMMENT_STATE][RETURN_CHAR] = START_STATE;
    mLegalMoves[LINECOMMENT_STATE][EOF_CHAR] = EOF_STATE;

    // Initialize mCorrespondingTokenTypes
    for (int i = 0; i < LAST_STATE; i++)
    {
        mCorrespondingTokenTypes[i] = BAD_TOKEN;
    }

    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[LTHAN_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[LEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[GTHAN_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[GEQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[NEQUAL_STATE] = NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[SCOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[EOF_STATE] = ENDFILE_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType &
                                                                       correspondingTokenType)
{
    // convert the input character into an input character type
    CharacterType charType = BAD_CHAR;

    if (isdigit(currentCharacter))
        charType = DIGIT_CHAR;
    if (isalpha(currentCharacter))
        charType = LETTER_CHAR;
    if (currentCharacter == '\n')
        charType = RETURN_CHAR;
    if (isspace(currentCharacter) && currentCharacter != '\n')
        charType = WHITESPACE_CHAR;
    if (currentCharacter == '+')
        charType = PLUS_CHAR;
    if (currentCharacter == '-')
        charType = MINUS_CHAR;
    if (currentCharacter == '*')
        charType = TIMES_CHAR;
    if (currentCharacter == '/')
        charType = DIVIDE_CHAR;
    if (currentCharacter == '!')
        charType = NOT_CHAR;
    if (currentCharacter == ';')
        charType = SCOLON_CHAR;
    if (currentCharacter == '<')
        charType = LTHAN_CHAR;
    if (currentCharacter == '>')
        charType = GTHAN_CHAR;
    if (currentCharacter == '(')
        charType = LPAREN_CHAR;
    if (currentCharacter == ')')
        charType = RPAREN_CHAR;
    if (currentCharacter == '{')
        charType = LCURLY_CHAR;
    if (currentCharacter == '}')
        charType = RCURLY_CHAR;
    if (currentCharacter == '=')
        charType = ASSIGNMENT_CHAR;
    if (currentCharacter == EOF)
        charType = EOF_CHAR;

    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][charType];
    return mCurrentState;
}