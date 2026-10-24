#include <stdio.h>

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

        return 0;
    }

    return 1;
    
}


int parse_variable(Parser *p){
    
    if(match(p , TOKEN_INT_KEY)) {
        error(p , "expected an \"int\"\n");
        return 1;
    } 
    

    if(match(p , TOKEN_IDENTIFIER)) {
        error(p , "expected an identifier\n");
        return 1;
    }
    

    if(match(p , TOKEN_INIT)) {
        error(p , "expected an \":=\"\n");
        return 1;
    }
    

    if(match(p , TOKEN_INT_LITERAL)) {
        error(p , "expected an int literal\n");
        return 1;
    }
    

    if(match(p , TOKEN_SEMICOLON)) {
        error(p , "expected an \";\"\n");
        return 1;
    }
    
    return 0;

}

int section_announcement(Parser *p)
{
    if(match(p , TOKEN_SECTION)) {
        error(p , "expected an \"@section@\"\n");
        return 1;
    } 

    if(match(p , TOKEN_COLON)) {
        error(p , "expected an \":\"\n");
        return 1;
    }

    while(!check(p , TOKEN_END_SEC))
    {
        if(parse_variable(p)) {return 1;}
    }



    if(match(p , TOKEN_END_SEC)) {
        error(p , "expected an \"@end@\"\n");
        return 1;
    }

    if(match(p , TOKEN_SEMICOLON)) {
        error(p , "expected an \";\"\n");
        return 1;
    }

    return 0;
}