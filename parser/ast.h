#pragma once

#include "../lexer/Ltoken.h"

struct SymbolTable;
struct ASTNode;

typedef enum {

    NODE_BIN_OP,            // any binary operation
    NODE_INT,               // integer    (INT)
    NODE_IDENT,             // identidier (STR)
    NODE_ASSIGN,            // x = a + 5
    NODE_SECTION,           // @data@ -> code
    NODE_PROGRAM,           // root 
    NODE_INITIALIZATION,    // inz: ...
    NODE_MAINS,             // main section
    NODE_FUNCS,             // functions section
    NODE_DATAS,             // data section (variable assigment)
    NODE_ENDS,              // end of programm
    NODE_USE,               // use files (aka include)

} NODEType;

typedef struct ASTNode{

    NODEType type;      // ast node type

    union {

        int value;          // node int value
        char* identifier;   // node string for token identifier
    
        

        struct {

            struct ASTNode* left;
            struct ASTNode* right;

            char operator;

        } BINARY_OPERATION;

        struct {

            char* variable;
            struct ASTNode* expression;


        } ASSIGN;

        struct {

            char* variable;
            TOKEN_TYPE data_type;
            struct ASTNode* right;

        } INZ;

        struct {

            char* section_name;
            int statement_count;
            struct ASTNode** statements;

        } SECTION;   
        
        struct {

            int sections_count;
            struct ASTNode** sections;

        } PROGRAM;
    


    };

} ASTNode;

int eval(ASTNode* n , struct SymbolTable *env);

