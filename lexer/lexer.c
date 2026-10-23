#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Ltoken.h"
#include "lexer.h"
#include "token_r.h"

#define PUNCT_TABLE_COUNT   (sizeof(PUNCT_RULES) / sizeof(PUNCT_RULES[0]))
#define KEYWORDS_COUNT      (sizeof(KEYWORDS) / sizeof(KEYWORDS[0]))

static const opToken PUNCT_RULES[] = {
    {"===", TOKEN_T_EQUALS},
    {":=",  TOKEN_INIT},
    {"==",  TOKEN_D_EQUALS},
    {"=",   TOKEN_EQUALS},
    {";",   TOKEN_SEMICOLON},
    {",",   TOKEN_COMMA},
    {".",   TOKEN_DOT},
    {":",   TOKEN_COLON},
    {"(",   TOKEN_LPAREN},
    {")",   TOKEN_RPAREN},
    {"{",   TOKEN_LBRACE},
    {"}",   TOKEN_RBRACE},
    {"%",   TOKEN_PERCENT},
    {"+",   TOKEN_PLUS},
    {"-",   TOKEN_MINUS},
    {"/", TOKEN_DIVIDE},
    {"*" , TOKEN_MULTIPLY}
};


static const keyToken KEYWORDS[] = {

    // DATA TYPES:

    {"INT" ,    TOKEN_INT_KEY       , 3},
    {"DOUBLE" , TOKEN_DOUBLE_KEY    , 6},
    {"STR" ,    TOKEN_STR_KEY       , 3},
    {"REAL" ,   TOKEN_REAL          , 4},
    {"LONG" ,   TOKEN_LONG          , 4},
    {"CHAR" ,   TOKEN_CHAR          , 4},
    {"BYTE" ,   TOKEN_BYTE          , 4},
    {"VOID" ,   TOKEN_VOID          , 4},

    // PROPERTIES:

    {"CONST" ,  TOKEN_CONST         , 5},
    {"STATIC" , TOKEN_STATIC        , 6},

    // BASE SECTIONS:

    {"@DATA@" , TOKEN_DATA_SEC      , 6},
    {"@END@" ,  TOKEN_END_SEC       , 5},
    {"@FUNC@" , TOKEN_FUNC_SEC      , 6},
    {"@USE@" ,  TOKEN_USE_SEC       , 5},

};


int addToken(Lexer *lex, TOKEN token)
{
    if(lex->length >= lex->capacity)
    {
        lex->capacity *= 2;
        TOKEN *nw = realloc(lex->token_arr , lex->capacity * sizeof(TOKEN));
        if(nw == NULL)
        {
            printf("Error with reallocated memory.\n");
            lex->capacity /= 2;

            
            return 1;
        }
        lex->token_arr = nw;

        
    }

    lex->token_arr[lex->length++] = token;

    return 0;
}

Lexer lexer_init(size_t cap){

    Lexer l;

    l.capacity =    cap;
    l.length =      0;
    l.token_arr =   malloc(sizeof(TOKEN) * cap);


    return l;
    
}

int lexlz(const char* source , size_t length , Lexer *result)
{

    if(source == NULL || length <= 0)
    {
        printf("Error : invalid data.\n");
        return 1;
    }

    Lexer lexs = lexer_init(256);

    size_t pos = 0;

    while(pos < length)
    {

        if (isspace((unsigned char)source[pos]))
        {
            pos++;
            continue;
        }

        if(isdigit((unsigned char)source[pos]))
        {
            int lng = 0;
            size_t spos = pos;
        
            char lexeme[128];

            while(pos < length && isdigit((unsigned char)source[pos]))
            {
                if(lng < 127)
                {
                    lexeme[lng++] = source[pos];
                }
                pos++;
            }

            lexeme[lng] = '\0';

            TOKEN t = CreateToken(TOKEN_INT_LITERAL , spos , lng , lexeme);
            if(addToken(&lexs , t) != 0)
            {
                printf("error with addToken()\n");
                return 1;
            }

            continue;
            
        }

        if(isalpha((unsigned char)source[pos]))
        {
            size_t startPosition = pos;
            int match = 0;

            for(size_t i = 0 ; i < KEYWORDS_COUNT ; i++)
            {
                size_t keywordLength = KEYWORDS[i].keyLen;

                if(pos + keywordLength <= length && strncmp(&source[pos] , KEYWORDS[i].keyword , keywordLength) == 0)
                {
                    TOKEN t = CreateToken(KEYWORDS[i].type , startPosition , keywordLength , KEYWORDS[i].keyword);
                    if(addToken(&lexs , t) != 0)
                    {
                        printf("error with creating keyword token ../lexer/lexer.c\n");
                        return 1;
                    }

                    pos += keywordLength;
                    match = 1;

                    break;
                }
            }

            if(match)
            {
                continue;
            }

            
            
        }

        if(source[pos] == '$')
        {
            size_t startPosition = pos;
            pos++;

            while(pos < length && (isalnum((unsigned char)source[pos]) || source[pos] == '_'))
            {
                pos++;
            }

            size_t variableLen = pos - startPosition;

            if(variableLen == 0)
            {
                printf("error: expected a variable name after '$'\n");
                return 1;
            }

            char *variableName = malloc(variableLen + 1);
            if(variableName == NULL) return 1;

            memcpy(variableName , source + startPosition , variableLen);
            variableName[variableLen] = '\0';

            TOKEN t = CreateToken(TOKEN_IDENTIFIER , startPosition , variableLen, variableName);
            if(addToken(&lexs , t) != 0)
            {
                printf("error with create identifier token\n");
                free(variableName);
                return 1;
            }

            free(variableName);
            continue;
        }

        if(ispunct((unsigned char)source[pos]))
        {
            size_t startPosition = pos;
            int match = 0;

            for(size_t i = 0 ; i < PUNCT_TABLE_COUNT ; i++)
            {
                size_t operatorLength = strlen(PUNCT_RULES[i].operator);

                if(pos + operatorLength <= length && strncmp(&source[pos] , PUNCT_RULES[i].operator , operatorLength) == 0)
                {
                    TOKEN t = CreateToken(PUNCT_RULES[i].type , startPosition , operatorLength , PUNCT_RULES[i].operator);
                    if(addToken(&lexs , t) != 0)
                    {
                        printf("error with creating operator token ../lexer/lexer.c\n");
                        return 1;
                    }

                    pos += operatorLength;
                    match = 1;

                    break;
                }
            }

            if(match)
            {
                continue;
            }

            printf("error: unknown character\n");
            return 1;

        }


        
    }

    
    *result = lexs;
    return 0;
}

