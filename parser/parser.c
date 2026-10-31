#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/Ltoken.h"

#include "parser.h"
#include "hash_t.h"
#include "ast.h"


static void error(Parser *p , const char* message)
{
    printf("syntax error : %s" , message);
}

Parser parse_init(TOKEN* token_array , size_t current_pos , size_t count)
{
    Parser parser;

    parser.token_array = token_array;
    parser.current_pos = current_pos;
    parser.count = count;

    return parser;

}

int universalType(TOKEN_TYPE type)
{
    return type == TOKEN_INT_KEY ||
        type == TOKEN_DOUBLE_KEY ||
        type == TOKEN_STR_KEY ||
        type == TOKEN_REAL ||
        type == TOKEN_BYTE ||
        type == TOKEN_CHAR ||
        type == TOKEN_BOOL || 
        type == TOKEN_LONG || 
        type == TOKEN_VOID;

}

ASTNode* createAST(NODEType type)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    if(node == NULL) exit(1);

    node->type = type;
    return node;
}

static TOKEN* peek(Parser *p)
{
    return p->current_pos < p->count ? &p->token_array[p->current_pos] : NULL;
}

static TOKEN* advance(Parser *p)
{
    TOKEN *t = peek(p);
    if(t) p->current_pos++;

    return t;
}

static int check(Parser *p , TOKEN_TYPE type)
{
    TOKEN *t = peek(p);

    return t && t->type == type;
}

static int match(Parser *p , TOKEN_TYPE type)
{
    if(check(p , type))
    {
        advance(p);

        return 1;
    }

    return 0;
    
}

ASTNode* parse_program(Parser *p)
{
    ASTNode* program = createAST(NODE_PROGRAM);

    while(peek(p)->type != TOKEN_EOF)
    {
        TOKEN* t = peek(p);

        if(t->type == TOKEN_DATA_SEC)
        {

        }
        else if (t->type == TOKEN_FUNC_SEC)
        {

        }
        else if (t->type == TOKEN_USE_SEC)
        {

        }
        else if (t->type == TOKEN_SECTION)
        {
            
        }

        
    }

}


ASTNode* parse_inz(Parser *p)
{
    if(!match(p , TOKEN_INZ))
    {
        error(p , "syntax error: expected a \"inz\"  \n");
        return NULL;
    }

    ASTNode* inz = createAST(NODE_INITIALIZATION);

    if(!match(p , TOKEN_COLON)){
        error(p , "syntax error: expected an \":\"\n");
        free(inz);
        return NULL;
    }

    TOKEN* current_t = peek(p);
    if(!universalType(current_t->type))
    {
        error(p , "syntax error: expected an type\n");
        free(inz);
        return NULL;
    }

    inz->INZ.data_type = current_t->type;
    advance(p);

    TOKEN* var_tok = advance(p);
    if(var_tok->type != TOKEN_VARIABLE){
        error(p , "syntax error: expected an variable name\n");
        free(inz);
        return NULL;
    }
    inz->INZ.variable = strdup(var_tok->value);

    if(!match(p , TOKEN_INIT)){
        error(p , "syntax error: expected an \":=\"\n");

        free(inz->INZ.variable);
        free(inz);

        return NULL;
    }

    TOKEN* tokenlit = advance(p);
    if(tokenlit->type != TOKEN_INT_LITERAL){
        error(p , "syntax error: expected an int literal\n");

        free(inz->INZ.variable);
        free(inz);

        return NULL;
    }

    ASTNode *expr_node = createAST(NODE_INT);
    expr_node->value = atoi(tokenlit->value);
    inz->INZ.right = expr_node;

    if(!match(p , TOKEN_SEMICOLON)){
        error(p , "syntax error: expected an \";\"\n");

        free(inz->INZ.variable);
        free(inz);

        return NULL;
    }


    return inz;


}


int parse_variable(Parser *p){
    
    if(!match(p , TOKEN_INT_KEY)) {
        error(p , "expected an \"int\"\n");
        return 1;
    } 
    

    if(!match(p , TOKEN_IDENTIFIER)) {
        error(p , "expected an identifier\n");
        return 1;
    }
    

    if(!match(p , TOKEN_INIT)) {
        error(p , "expected an \":=\"\n");
        return 1;
    }
    

    if(!match(p , TOKEN_INT_LITERAL)) {
        error(p , "expected an int literal\n");
        return 1;
    }
    

    if(!match(p , TOKEN_SEMICOLON)) {
        error(p , "expected an \";\"\n");
        return 1;
    }
    
    return 0;

}

int section_announcement(Parser *p)
{
    if(!match(p , TOKEN_SECTION)) {
        error(p , "expected an \"@section@\"\n");
        return 1;
    } 

    if(!match(p , TOKEN_COLON)) {
        error(p , "expected an \":\"\n");
        return 1;
    }

    while(!check(p , TOKEN_END_SEC))
    {
        if(parse_variable(p)) {return 1;}
    }



    if(!match(p , TOKEN_END_SEC)) {
        error(p , "expected an \"@end@\"\n");
        return 1;
    }

    if(!match(p , TOKEN_SEMICOLON)) {
        error(p , "expected an \";\"\n");
        return 1;
    }

    return 0;
}