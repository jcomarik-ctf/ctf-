#pragma once

typedef enum {
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_DIVIDE,       // /
    TOKEN_MULTIPLY,     // *
    TOKEN_INT_LITERAL,  // 123
    TOKEN_EQUALS,       // =
    TOKEN_SEMICOLON,    // ;
    TOKEN_COLON,        // :
    TOKEN_IDENTIFIER,   // any word
    TOKEN_D_EQUALS,     // ==
    TOKEN_T_EQUALS,     // ===
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_DOT,          // .
    TOKEN_COMMA,        // ,
    TOKEN_UNKNOWN,      // UNKNOWN object
    TOKEN_PERCENT,      // %
    TOKEN_QUOTE,        // ""
    TOKEN_STRING,       // "string"

} TOKEN_TYPE;

typedef struct {

    TOKEN_TYPE type;    // TYPE OF TOKEN
    char *value;     // VALUE

    size_t cpos;        // current position (start)
    size_t lng;         //lenght of token


} TOKEN;
