#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_t.h"

SymbolTable* create_table(int size)                 
{
    SymbolTable* env = malloc(sizeof(SymbolTable));
    env->elements = calloc(size, sizeof(HashNode*));

    env->size = size;

    return env;
}

unsigned int hashFunc(const char* ident){       // generate unuque hash code based on char* key (ident)

    unsigned int result = 5381;                 // start simple int

    for(int i = 0 ; ident[i] != '\0' ; ++i)
    {
        result = (result * 33 + ident[i]);      // djb2 alg
    }

    return result;
}

int set_var(SymbolTable* env , char* ident , int value){


    unsigned int hcode = hashFunc(ident);           // hash code based on identifier
    int index = hcode % env->size;                  // generate unique table index 

    HashNode* current = env->elements[index];
    while(current != NULL)                          // we search exist KEY 
    {
        if(strcmp(current->key , ident) == 0)
        {
            current->value = value;

            return 0;
        }

        current = current->next;

    }                                               // if KEY not exist , we create them on new node 

    HashNode* new_node = malloc(sizeof(HashNode));  // allocate memory to new node

    new_node->key = ident;
    new_node->value = value;

    new_node->next = env->elements[index];          // we pretend be a FIRST element , so save the current first element (next),
    env->elements[index] = new_node;                // and new_node now is a first element , and next - second

    return 0;
    

}

int get_var(SymbolTable* env , char* ident){

    unsigned int hcode = hashFunc(ident);
    int index = hcode % env->size;

    HashNode* current = env->elements[index];

    while(current != NULL)
    {
        if(strcmp(current->key , ident) == 0)
        {
            return current->value;
        }

        current = current->next;
    }

    printf("error : variable not found\n");
    return 1;

}

void freeTable(SymbolTable* env)
{
    if(env == NULL) return;

    
    for(int i = 0 ; i < env->size ; ++i)
    {
        HashNode* current = env->elements[i];
        
        while(current != NULL)
            {
                HashNode* next_node = current->next;

                if(current->key != NULL)
                {
                    free(current->key);
                }
                free(current);

                current = current->next;
            }   
    }

    free(env->elements);
    free(env);

}

