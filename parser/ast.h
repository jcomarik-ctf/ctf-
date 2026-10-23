#pragma once

typedef enum {

    NODE_BIN_OP,        // any binary operation
    NODE_INT,           // integer    (INT)
    NODE_IDENT,         // identidier (STR)
    NODE_ASSIGN,        // x = a + 5
    NODE_SECTION,       // @data@ -> code
    NODE_PROGRAM,       // root 

} NODEType;

typedef struct {

    NODEType type;      // ast node type

    union {

        int value;          // node int value
        char* identifier;   // node string for token identifier
    
        struct {

            ASTNode* left;
            ASTNode* right;

            char operator;

        } BINARY_OPERATION;

        struct {

            char* variable;
            ASTNode* expression;


        } ASSIGN;

        struct {

            char* section_name;
            int statement_count;
            ASTNode** statements;

        } SECTION;   
        
        struct {

            int sections_count;
            ASTNode** sections;

        } PROGRAM;
    


    };

} ASTNode;

int eval(ASTNode* n , SymbolTable *env);

