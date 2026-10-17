#pragma once

typedef enum {
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_DIVIDE,       // /
    TOKEN_MULTIPLY,     // *
    TOKEN_NUMBER,       // INT
    TOKEN_EQUALS,       // =
    TOKEN_SEMICOLON,    // ;
    TOKEN_COLON,        // :
    TOKEN_IDENTIFIER    // any word

} TOKEN_TYPE;

typedef struct {

    TOKEN_TYPE type;    // TYPE OF TOKEN
    char *value;     // VALUE

    size_t cpos;        // current position (start)
    size_t lng;         //lenght of token


} TOKEN;
