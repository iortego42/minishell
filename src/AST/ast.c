#include "ast.h"

t_Ast   *new_ast_node(t_Ast tree) {
    t_Ast *root;

    root = malloc(sizeof(t_Ast));
    if (!root)
        return (NULL);
    *root = tree;
    if (root->tag == Expression)
        constructor(root);
    return (root);
}

t_bool free_ast_node(t_Ast    **node) {
    t_Ast   *ptr;
    if (!node || !*node)
        return (TRUE);
    ptr = *node;
    if (ptr->tag == Literal)
    {
        ptr->u_d.Literal.freezer(&ptr->u_d.Literal);
        ptr->u_d.Literal.data = NULL;
    }
    else if (ptr->tag == Operator){
        if (!free_ast_node(&ptr->u_d.Operator.left)
            || !free_ast_node(&ptr->u_d.Operator.right))
            return (FALSE);
    }
    else if (ptr->tag == Expression)
        ptr = NULL; 
    else
        return (FALSE);
    free(*node);
    *node = NULL;
    return (TRUE);
}

void    *operate(t_Ast  **this) {
    void    *r_v;
    void    *l_v;
    void    *data;

    if (this[0]->tag != Operator)
        return NULL; 
    if (this[0]->u_d.Operator.left->tag == Literal)
        l_v = this[0]->u_d.Operator.left->u_d.Literal.data;
    else 
        l_v = operate(&this[0]->u_d.Operator.left);
    if (this[0]->u_d.Operator.right->tag == Literal)
        r_v = this[0]->u_d.Operator.right->u_d.Literal.data;
    else 
        r_v = operate(&this[0]->u_d.Operator.right);
    data = this[0]->u_d.Operator.Resolve(l_v, r_v);
    if (!this[0]->u_d.Operator.left)
        free(l_v);
    if (!this[0]->u_d.Operator.right)
        free(r_v);
    if (!free_ast_node(this)) printf("There was an Error\n");
    return (data);
}

t_Ast   *solve_cmd(t_Ast  *this)
{
    int     i;
    int     sym_c;
    t_Ast   *tree;

    lexer(g_sh.cmd); // check true or false
    tree = AST_NODE(Expression, 0, ft_strlen(g_sh.cmd) + 1);
    constructor(tree);
    operate(&tree);
    return (tree);
}