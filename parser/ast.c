#include "ast.h"



int eval(ASTNode* n){

    switch (n->type)
    {
        case NODE_INT: return n->value;
        case NODE_BIN_OP: 

            int l = eval(n->left);
            int r = eval(n->right);

            switch (n->op){
                case '+': return l + r;
                case '-': return l - r;
                case '*': return l * r;
                case '/': return l / r;
            }
            


        default: printf("error : invalid AST node type\n") ; return 1;
        
    }

}