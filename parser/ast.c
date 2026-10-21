#include "ast.h"
#include "hash_t.h"

int eval(ASTNode* n , SymbolTable *env){

    switch (n->type)
    {
        case NODE_INT: 
            return n->value;
        case NODE_BIN_OP: 

            int l = eval(n->left , env);
            int r = eval(n->right , env);

            switch (n->op){
                case '+': return l + r;
                case '-': return l - r;
                case '*': return l * r;
                case '/': return l / r;
            }
        
            case NODE_ASSIGN: 
                int value = eval(n->right , env);

                set_var(env , n->left->identifier , value);




        default: printf("error : invalid AST node type\n") ; return 1;
        
    }

}