#pragma once

typedef enum {

    NODE_BIN_OP,        // any binary operation
    NODE_INT,           // integer    (INT)
    NODE_IDENT,         // identidier (STR)


} NODEType;

typedef struct {

    NODEType type;      // ast node type

    int value;          // node int value
    char* identifier;   // node string for token identifier
    char op;

    ASTNode* left;      // left subtree
    ASTNode* right;     // right subtree

} ASTNode;

int eval(ASTNode* n);

