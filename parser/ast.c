#include "ast.h"
#include "hash_t.h"

int eval(ASTNode* n , SymbolTable *env){

    switch (n->type)
    {
        case NODE_INT: {return n->value;}
        case NODE_BIN_OP: {

            int l = eval(n->BINARY_OPERATION.left , env);
            int r = eval(n->BINARY_OPERATION.right , env);

            switch (n->BINARY_OPERATION.operator){
                case '+': return l + r;
                case '-': return l - r;
                case '*': return l * r;
                case '/': return l / r;
            }
            break;
        }   

        case NODE_ASSIGN: {

            int value = eval(n->ASSIGN.expression , env);

            set_var(env , n->ASSIGN.variable , value);

            return value;

        }


        default: printf("error : invalid AST node type\n") ; return 1;
        
    }

}