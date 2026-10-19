#pragma once 

#include "Ltoken.h"

typedef struct {

    size_t capacity;
    size_t length;

    TOKEN* token_arr;


} Lexer;

int lexlz(const char* source , size_t length);

int addToken(Lexer *lex, TOKEN token);

Lexer lexer_init(size_t cap);

void printTokens(Lexer* lex);