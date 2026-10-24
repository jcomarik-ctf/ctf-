#pragma once

typedef enum {

    // arithmetic operators:

    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_DIVIDE,       // /
    TOKEN_MULTIPLY,     // *
    
    // punct:
    
    TOKEN_EQUALS,       // =
    TOKEN_SEMICOLON,    // ;
    TOKEN_COLON,        // :
    TOKEN_D_EQUALS,     // ==
    TOKEN_T_EQUALS,     // ===
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_DOT,          // .
    TOKEN_COMMA,        // ,
    TOKEN_PERCENT,      // %
    TOKEN_INIT,         // :=
    
    // base sections:
    
    TOKEN_END_SEC,      // @end@
    TOKEN_DATA_SEC,     // @data@
    TOKEN_FUNC_SEC,     // @func@
    TOKEN_USE_SEC,      // @use@
    TOKEN_PROGRAM,      // start point of whole program

    TOKEN_RETURN,       // return

    // data types:

    TOKEN_INT_KEY,      // int 
    TOKEN_DOUBLE_KEY,   // double
    TOKEN_STR_KEY,      // string
    TOKEN_REAL,         // real (float)
    TOKEN_LONG,         // long 
    TOKEN_CHAR,         // char
    TOKEN_BYTE,         // byte
    TOKEN_VOID,         // void
    TOKEN_BOOL,         // bool 

    // "useful" data:

    TOKEN_IDENTIFIER,   // any word
    TOKEN_SECTION,      // @SECTION@ - any section 
    TOKEN_INT_LITERAL,  // 123
    TOKEN_VARIABLE,     // $var
    TOKEN_STRING_Q,     // "string"
    TOKEN_FUNCTION,     // _function

    // properties:

    TOKEN_CONST,        // const 
    TOKEN_STATIC,       // static
    TOKEN_NULL,         // NULL

    // instructions:

    TOKEN_INZ,          // initialization 
    TOKEN_MOV,          // rewrite variable
    TOKEN_ADD,          // add value to varible
    TOKEN_SBT,          // omagat
    TOKEN_MLT,          // multiply variable
    TOKEN_DVD,          // divide variable
    TOKEN_FNC_DECL,     // fnc: in @func@
    

} TOKEN_TYPE;

typedef struct {

    TOKEN_TYPE type;    // TYPE OF TOKEN
    char *value;        // VALUE

    size_t cpos;        // current position (start)
    size_t lng;         //lenght of token


} TOKEN;
