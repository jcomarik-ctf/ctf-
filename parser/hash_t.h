#pragma once

#include <stdio.h>

int hashFunc(const char* ident);        // from key to hash code

SymbolTable* create_table(int size);    // init hash table 


typedef struct              // the struct of one node
{
    int value;              // value (key -> value)
    char* key;              // key

    HashNode* next;         // the next node in hash table


} HashNode;


typedef struct {            // the table 

    int size;               // count of elements (node)
    HashNode** elements;    // array of node's arrays 



} SymbolTable;

int get_var(SymbolTable* env , char* ident);                // get variable in table

int set_var(SymbolTable* env , char* ident , int value);    // set new variable & change value

void freeTable(SymbolTable* env);                           // memory free 