#include <stdio.h>

#define MAX_SIZE 101

int hashFunc(const char* ident);

SymbolTable* create_table(int size);


typedef struct 
{
    int value;
    char* key;

    HashNode* next;


} HashNode;


typedef struct {

    int size;
    HashNode** elements;



} SymbolTable;

int get_var(SymbolTable* env , char* ident);

int set_var(SymbolTable* env , char* ident , int value);