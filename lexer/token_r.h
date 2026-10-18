#pragma once

#include <stddef.h>
#include "Ltoken.h"

TOKEN CreateToken(TOKEN_TYPE type , size_t current_position , size_t length , const char *value);

void SaveToken(const TOKEN token );