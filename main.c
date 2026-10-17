#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "Ltoken.h" // типы токенов и сам токен
#include "token_r.h"
#include <string.h>



int main()
{
   
    
    size_t token_count = 0; // d
    TOKEN token_arr[256];
    
    // начало чтения с файла:
    FILE* file = fopen("test.txt" , "r");

    if(file == NULL)
    {
        printf("Error!\n");
        return 1;
    }

    size_t pos = 0;
    int ch;

    while((ch = fgetc(file)) != EOF)
    {
        if(isalpha(ch))
        {
            int lch , lng = 0;
            size_t start = pos;

            char lexeme[256];
            lexeme[lng++] = ch;
            
            while((lch = fgetc(file)) != EOF && isalpha(lch))
            {
                lexeme[lng++] = (char)lch;
                
                pos++;

            }

            lexeme[lng] = '\0';

            if(lch != EOF)
            {
                ungetc(lch , file);
            }

            TOKEN tk = CreateToken(TOKEN_IDENTIFIER , start , lng , lexeme);

            printf("[%s%d] len=%zu (\"%s\")\n",
           "TOKEN_IDENTIFIER", tk.type ,  lng, tk.value);

            
            
        }
        if(isdigit(ch))
        {
            int lch , lng = 0;
            size_t start = pos;

            char lexeme[256];
            lexeme[lng++] = ch;
            
            while((lch = fgetc(file)) != EOF && isdigit(lch))
            {
                lexeme[lng++] = (char)lch;
                
                pos++;

            }

            lexeme[lng] = '\0';

            if(lch != EOF)
            {
                ungetc(lch , file);
            }

            TOKEN tk = CreateToken(TOKEN_NUMBER , start , lng , lexeme);

            printf("[%s%d] len=%zu (\"%s\")\n",
           "TOKEN_NUMBER" , tk.type , lng, tk.value); // d

            
            
        }
        if(ispunct(ch))
        {
            int lch , lng = 0;
            size_t start = pos;

            char lexeme[256];
            lexeme[lng++] = ch;
            
            while((lch = fgetc(file)) != EOF && ispunct(lch))
            {
                lexeme[lng++] = (char)lch;
                
                pos++;

            }

            lexeme[lng] = '\0';

            if(lch != EOF)
            {
                ungetc(lch , file);
            }

            TOKEN tk = CreateToken(TOKEN_SEMICOLON , start , lng , lexeme);

            printf("[%s%d] len=%zu (\"%s\")\n",
           "TOKEN_PUNCT" , tk.type , lng, tk.value); // d

            
            
        }
        
        pos++;
    }


    fclose(file);

    return 0;
}