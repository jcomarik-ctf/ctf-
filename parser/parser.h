#pragma once

#include "../lexer/Ltoken.h"
#include "../parser/ast.h"


typedef struct {

    TOKEN* token_array;
    size_t current_pos;
    size_t count;

    int line;
    

} Parser;

ASTNode* parse_inz(Parser *p);

ASTNode* parse_program(Parser *p);

ASTNode* createAST(NODEType type);

static void error(Parser *p , const char* message);

Parser parse_init(TOKEN* token_array , size_t current_pos , size_t count);

int section_announcement(Parser *p);

int parse_variable(Parser *p);