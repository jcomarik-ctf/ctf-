#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Ltoken.h"
#include "lexer.h"
#include "token_r.h"


int lexlz(const char* source , size_t length)
{
    if(source == NULL || length <= 0)
    {
        printf("Error : invalid data.\n");
        return 1;
    }

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

            printf("[%s] length = %zu\n" , t.value , t.lng);

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

            printf("[%s] length = %zu\n" , t.value , t.lng);

            continue;
            
        }

        if(ispunct((unsigned char)source[pos]))
        {
            
            size_t spos = pos;
        
            if(pos + 2 < length && source[pos] == '=' && source[pos+1] == '=' && source[pos+2] == '='){
                TOKEN t = CreateToken(TOKEN_T_EQUALS , spos , 3 , "===");
                pos += 3;
                continue;
            }
            else if(pos + 1 < length && source[pos] == '=' && source[pos+1] == '='){
                TOKEN t = CreateToken(TOKEN_D_EQUALS , spos , 2 , "==");
                pos += 2;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == '='){
                TOKEN t = CreateToken(TOKEN_EQUALS , spos , 1 , "=");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(pos + 1 < length && source[pos] == ':' && source[pos+1] == '='){
                TOKEN t = CreateToken(TOKEN_INIT , spos , 1 , ":=");
                pos += 2;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == ';'){
                TOKEN t = CreateToken(TOKEN_SEMICOLON , spos , 1 , ";");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == ':'){
                TOKEN t = CreateToken(TOKEN_COLON , spos , 1 , ":");
                pos += 1;
                continue;
            }
            else if(source[pos] == ','){
                TOKEN t = CreateToken(TOKEN_COMMA , spos , 1 , ",");
                pos += 1;
                continue;
            }
            else if(source[pos] == '.'){
                TOKEN t = CreateToken(TOKEN_DOT , spos , 1 , ".");
                pos += 1;
                continue;
            }
            else if(source[pos] == '('){
                TOKEN t = CreateToken(TOKEN_LPAREN , spos , 1 , "(");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == ')'){
                TOKEN t = CreateToken(TOKEN_RPAREN , spos , 1 , ")");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == '{'){
                TOKEN t = CreateToken(TOKEN_LBRACE , spos , 1 , "{");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == '}'){
                TOKEN t = CreateToken(TOKEN_RBRACE , spos , 1 , "}");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == '%'){
                TOKEN t = CreateToken(TOKEN_PERCENT , spos , 1 , "%");
                pos += 1;
                printf("[%s] length = %zu\n" , t.value , t.lng);
                continue;
            }
            else if(source[pos] == '+'){
                TOKEN t = CreateToken(TOKEN_PLUS , spos , 1 , "+");
                pos += 1;
                continue;
            }
            else if(source[pos] == '-'){
                TOKEN t = CreateToken(TOKEN_MINUS , spos , 1 , "-");
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
                printf("[%s] length = %zu\n" , t.value , t.lng);
                free(val);

                continue;
                
            }

            else {

                printf("Error: unknown character.\n");
                return 1;
            }
            
            
        }


        //pos++;
    }

    return 0;
}

