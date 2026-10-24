#pragma once

#include "../lexer/Ltoken.h"


typedef struct {

    TOKEN* token_array;
    size_t current_pos;
    size_t count;

    int line;
    

} Parser;

static void error(Parser *p , const char* message);

Parser parse_init(TOKEN* token_array , size_t current_pos , size_t count);

int section_announcement(Parser *p);

int parse_variable(Parser *p);