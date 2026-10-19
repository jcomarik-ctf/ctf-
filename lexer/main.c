#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "Ltoken.h" // типы токенов и сам токен
#include "token_r.h"
#include "lexer.h"


void* allocm(char* olch , size_t* capacity , size_t* length)
{
    if(*length >= *capacity)
    {
        (*capacity) *= 2;

        char *nwch = malloc(sizeof(char) * (*capacity));
        if (nwch == NULL)
        {
            (*capacity) /= 2;
            
            return NULL;
        }

        for(size_t i = 0 ; i < (*length) ; ++i)
        {
            nwch[i] = olch[i];
        }

        free(olch);

        return nwch;

    } else {

        return olch;
    }

}



int main()
{
    // массив исходного текста 
    size_t capacity = 512 , length = 0;                 // вместимость динам. массива и длина 

    char* filearr = malloc(sizeof(char) * capacity);    // выделение памяти
    if(filearr == NULL){return 1;}

    // начало чтения с файла:
    FILE* file = fopen("test.txt" , "rb");
    if(file == NULL)
    {
        printf("Error! File not found.\n");
        free(filearr);   
        return 1;
    }

    // ------------------------------------

    while(1)
    {
        if(length >= capacity)
        {
            filearr = allocm(filearr , &capacity , &length);
            if(filearr == NULL)
            {
                printf("Error : memory not allocated.\n");
                fclose(file);
                return 1;
            }
        }

        size_t available = capacity - length;
        size_t bytes_read = fread((filearr + length), sizeof(char), available , file);

        if(bytes_read > 0)
        {
            length += bytes_read;
        }

        if(bytes_read < available)
        {
            if(ferror(file))
            {
                printf("Error in file reader!\n");
                free(filearr);   
                fclose(file);
                return 1;
            }

            if(feof(file))
            {
                break;
            }
        }

    }

    // ------------------------------------

    size_t pos = 0;
    
    
    if(lexlz(filearr , length) != 0){
        printf("Error with output.\n");
        fclose(file);
        return 1;
    }

    // debug only
    printf("%zu|%zu", capacity , length);




    fclose(file);

    free(filearr);   
    return 0;
}