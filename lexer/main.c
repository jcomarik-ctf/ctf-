#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "Ltoken.h" // типы токенов и сам токен
#include "token_r.h"
#include "lexer.h"

#include "../parser/parser.h"
#include "../parser/hash_t.h"



int main()
{
    // массив исходного текста 
    char* filearr;

    // начало чтения с файла:
    FILE* file = fopen("test.tj" , "rb");
    if(file == NULL)
    {
        printf("Error! File not found.\n");
        return 1;
    }

    
    if(fseek(file , 0 , SEEK_END) != 0)
    {
        printf("error with fseek()\n");
        fclose(file);
        
        return 1;
    }
    
    long l = ftell(file);

    if(l == -1L)
    {
        printf("error with ftell()\n");
        fclose(file);
        
        return 1;
    }

    if(fseek(file , 0 , SEEK_SET) == -1L)
    {
        printf("error with fseek()\n");
        fclose(file);
        
        return 1;
    }
    

    size_t length = 0;           // вместимость динам. массива и длина 

    filearr = malloc(l + 1);    // выделение памяти
    if(filearr == NULL){ fclose(file) ; return 1;}

    size_t readb = fread(filearr , 1 , l , file);
    if(readb != l && ferror(file))
    {
        printf("error with file read\n");
        free(filearr);
        fclose(file);

        return 1;
    }

    filearr[readb] = '\0';
    length = readb;

    
    Lexer lexeme_array = {0};                           // создаем структуру с данными массива токенов
    if(lexlz(filearr , length , &lexeme_array ) != 0){
        printf("Error with output.\n");
        free(filearr);
        fclose(file);

        return 1;
    }

    SymbolTable table = create_table(101);

    Parser parser = parse_init(lexeme_array.token_arr , 0 ,lexeme_array.length);

    
    // debug only
    /*for(size_t i = 0 ; i < lexeme_array.length ; i++)
    {
        printf("[\"%s\"] TYPE = %d , start pos = %d , length = %d\n" ,
             lexeme_array.token_arr[i].value,
             lexeme_array.token_arr[i].type ,
             lexeme_array.token_arr[i].cpos,
             lexeme_array.token_arr[i].lng);
            
    }*/



    printf("%d|%zu", l , length);

    fclose(file);
    free(filearr);  
    
    freeTable(&table);
    return 0;
}