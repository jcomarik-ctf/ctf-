#pragma once

#include <stdio.h>

typedef struct HashNode {    // the struct of one node
    int value;              // value (key -> value)
    char* key;              // key

    struct HashNode *next;         // the next node in hash table


} HashNode;


typedef struct SymbolTable {            // the table 

    int size;               // count of elements (node)
    HashNode** elements;    // array of node's arrays 



} SymbolTable;

unsigned int hashFunc(const char* ident);        // from key to hash code

SymbolTable* create_table(int size);                        // init hash table 

int get_var(SymbolTable* env , char* ident);                // get variable in table

int set_var(SymbolTable* env , char* ident , int value);    // set new variable & change value

void freeTable(SymbolTable* env);                           // memory free 