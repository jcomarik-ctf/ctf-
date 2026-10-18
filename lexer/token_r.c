#include "token_r.h"
#include "Ltoken.h"

#include <stdlib.h>
#include <string.h>


TOKEN CreateToken(TOKEN_TYPE type , size_t current_position , size_t length , const char *value)
{
    TOKEN now_tk;                       // local TOKEN var

    now_tk.type = type;                 // token type
    now_tk.cpos = current_position;     // current lexeme pos
    now_tk.lng = length;                // length of lexeme

    now_tk.value = malloc((length + 1) * sizeof(char));

    if(now_tk.value)
    {
        strcpy(now_tk.value , value);
    }

    

    return now_tk;
    
}