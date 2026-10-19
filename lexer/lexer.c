#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Ltoken.h"
#include "lexer.h"
#include "token_r.h"


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

            free(nw);
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

// debug only
void printTokens(Lexer* lex)
{
    if(lex->token_arr == NULL)
    {   
        printf("Error with memory allocate.\n");
        return;
    }

    for(size_t i = 0 ; i < lex->length ; i++)
    {
        printf("[\"%s\"] TYPE = %d , start pos = %d , length = %d\n" ,
             lex->token_arr[i].value,
             lex->token_arr[i].type ,
             lex->token_arr[i].cpos,
             lex->token_arr[i].lng);
            
    }
}

int lexlz(const char* source , size_t length)
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
        
        if(isalpha((unsigned char)source[pos]))
        {
            int lng = 0;
            size_t spos = pos;
        
            char lexeme[128];

            while(pos < length && isalpha((unsigned char)source[pos]))
            {
                if(lng < 127){
                    lexeme[lng++] = source[pos];
                }
                pos++;
            }

            lexeme[lng] = '\0';

            TOKEN t = CreateToken(TOKEN_IDENTIFIER , spos , lng , lexeme);
            addToken(&lexs , t);

            

            continue;
            
        }

        if(isdigit((unsigned char)source[pos]))
        {
            int lng = 0;
            size_t spos = pos;
        
            char lexeme[128];

            while(pos < length && isdigit((unsigned char)source[pos]))
            {
                if(lng < 127){
                    lexeme[lng++] = source[pos];
                }
                pos++;
            }

            lexeme[lng] = '\0';

            TOKEN t = CreateToken(TOKEN_INT_LITERAL , spos , lng , lexeme);
            addToken(&lexs , t);

            

            continue;
            
        }

        if(ispunct((unsigned char)source[pos]))
        {
            
            size_t spos = pos;
        
            if(pos + 2 < length && source[pos] == '=' && source[pos+1] == '=' && source[pos+2] == '='){
                TOKEN t = CreateToken(TOKEN_T_EQUALS , spos , 3 , "===");
                addToken(&lexs , t);
                pos += 3;
                continue;
            }
            else if(pos + 1 < length && source[pos] == '=' && source[pos+1] == '='){
                TOKEN t = CreateToken(TOKEN_D_EQUALS , spos , 2 , "==");
                addToken(&lexs , t);
                pos += 2;
                
                continue;
            }
            else if(source[pos] == '='){
                TOKEN t = CreateToken(TOKEN_EQUALS , spos , 1 , "=");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(pos + 1 < length && source[pos] == ':' && source[pos+1] == '='){
                TOKEN t = CreateToken(TOKEN_INIT , spos , 2 , ":=");
                addToken(&lexs , t);
                pos += 2;
                
                continue;
            }
            else if(source[pos] == ';'){
                TOKEN t = CreateToken(TOKEN_SEMICOLON , spos , 1 , ";");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(source[pos] == ':'){
                TOKEN t = CreateToken(TOKEN_COLON , spos , 1 , ":");
                addToken(&lexs , t);
                pos += 1;

                continue;
            }
            else if(source[pos] == ','){
                TOKEN t = CreateToken(TOKEN_COMMA , spos , 1 , ",");
                addToken(&lexs , t);
                pos += 1;

                continue;
            }
            else if(source[pos] == '.'){
                TOKEN t = CreateToken(TOKEN_DOT , spos , 1 , ".");
                addToken(&lexs , t);
                pos += 1;

                continue;
            }
            else if(source[pos] == '('){
                TOKEN t = CreateToken(TOKEN_LPAREN , spos , 1 , "(");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(source[pos] == ')'){
                TOKEN t = CreateToken(TOKEN_RPAREN , spos , 1 , ")");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(source[pos] == '{'){
                TOKEN t = CreateToken(TOKEN_LBRACE , spos , 1 , "{");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(source[pos] == '}'){
                TOKEN t = CreateToken(TOKEN_RBRACE , spos , 1 , "}");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(source[pos] == '%'){
                TOKEN t = CreateToken(TOKEN_PERCENT , spos , 1 , "%");
                addToken(&lexs , t);
                pos += 1;
                
                continue;
            }
            else if(source[pos] == '+'){
                TOKEN t = CreateToken(TOKEN_PLUS , spos , 1 , "+");
                addToken(&lexs , t);
                pos += 1;

                continue;
            }
            else if(source[pos] == '-'){
                TOKEN t = CreateToken(TOKEN_MINUS , spos , 1 , "-");
                addToken(&lexs , t);
                pos += 1;

                continue;
            }
            else if(source[pos] == '"'){
                size_t spos = pos;
                pos++;

                size_t start = pos;

                while(pos < length && source[pos] != '"')
                {
                    pos++;
                }

                size_t stlen = pos - start;

                if(pos >= length)
                {
                    printf("Error : unterminated string.\n");
                    return 1;
                }

                pos++;

                char *val = malloc(stlen + 1);
                if(val == NULL) return 1;

                memcpy(val , source + start , stlen);
                val[stlen] = '\0';

                TOKEN t = CreateToken(TOKEN_STRING , spos , stlen , val);
                addToken(&lexs , t);
                
                free(val);

                continue;
                
            }

            else {

                printf("Error: unknown character.\n");
                return 1;
            }
            
            
        }


        
    }

    printTokens(&lexs);
    
    return 0;
}

