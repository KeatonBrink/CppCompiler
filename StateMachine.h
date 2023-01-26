#pragma once

#include "Token.h"

enum MachineState
{
    START_STATE,
    IDENTIFIER_STATE,
    INTEGER_STATE,
    CANTMOVE_STATE,
    LTHAN_STATE,
    GTHAN_STATE,
    EQUAL_STATE,
    NOT_STATE,
    NEQUAL_STATE,
    LEQUAL_STATE,
    GEQUAL_STATE,
    INSERTION_STATE,
    PLUS_STATE,
    MINUS_STATE,
    TIMES_STATE,
    DIVIDE_STATE,
    LCURLY_STATE,
    RCURLY_STATE,
    LPAREN_STATE,
    RPAREN_STATE,
    SCOLON_STATE,
    EOF_STATE,
    ASSIGNMENT_STATE,
    LAST_STATE
};

enum CharacterType
{
    LETTER_CHAR,
    DIGIT_CHAR,
    WHITESPACE_CHAR,
    PLUS_CHAR,
    MINUS_CHAR,
    TIMES_CHAR,
    DIVIDE_CHAR,
    BAD_CHAR,
    NOT_CHAR,
    SCOLON_CHAR,
    LTHAN_CHAR,
    GTHAN_CHAR,
    LPAREN_CHAR,
    RPAREN_CHAR,
    LCURLY_CHAR,
    RCURLY_CHAR,
    ASSIGNMENT_CHAR,
    EOF_CHAR,
    LAST_CHAR
};

class StateMachineClass
{
public:
    StateMachineClass();
    MachineState UpdateState(char currentCharacter, TokenType &
                                                        correspondingTokenType);

private:
    MachineState mCurrentState;

    // The matrix of legal moves:
    MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

    // Which end-machine-states correspond to which token types.
    // (non end states correspond to the BAD_TOKEN token type)
    TokenType mCorrespondingTokenTypes[LAST_STATE];
};
