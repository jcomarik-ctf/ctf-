#include <stdio.h>
#include <stdlib.h>

#include "hash_t.h"

SymbolTable* create_table(int size)
{
    SymbolTable* env = malloc(sizeof(SymbolTable));
    env->elements = calloc(size, sizeof(HashNode*));

    env->size = size;

    return env;
}

unsigned int hashFunc(const char* ident){

    unsigned int result = 5381;

    for(int i = 0 ; ident[i] != '\0' ; ++i)
    {
        result = (result * 33 + ident[i]);
    }

    return result;
}

int set_var(SymbolTable* env , char* ident , int value){


    unsigned int hcode = hashFunc(ident);
    int index = hcode % env->size;

    if(env->elements[index] != NULL)
    {
        
        
        
    }
    

}

int get_var(SymbolTable* env , char* ident){

    
}

