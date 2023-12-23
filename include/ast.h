#ifndef AST_H
# define AST_H

/*
|   tag =>  Tag or Type of the data 
|   u_d =>  Data of the Tree
|
|   This is done to avoid bugs and avoid the program misinternpret
|   some region of the memory as an inapropiate data type.
|
|   u_d:    for every type of token will be an specific type of 
|           data defined. We can distinguish 3 of them:
|           - Operators: This ones will have left and right context
|                        of all the rest of the types, 2 operators
|                        can't be found together. they got a
|                        function which will be executed with the
|                        values of both context passed as params.
|           - Literals: The most simple data type, they do not have
|                       any context, just values. They can be
|                       obtained when expresions are resolved.
|           - Expression: This type will define an entire expression
|                         which can contain all the 3 existing types 
|                         inside. And expresion must be resolved in
|                         order to obtain a new group of Operators
|                         and Literals or just a Literal.
|
|
|
|
*/

# include "minishell.h"
# include "libft.h"
# define AST_NODE(tag, ...)\
        new_ast_node((t_Ast){tag, {.tag=(struct s_##tag){__VA_ARGS__}}})
typedef struct s_Ast t_Ast;
typedef enum {
    Operator,
    Literal
} t_tag;
typedef struct s_Operator t_O;
struct s_Operator {
    t_Ast   *left;
    t_Ast   *right;
    char    mask;
    void    *(*Resolve) (void *l_d, void *r_d);
    // void    *resolved_data;
};
typedef struct s_Literal t_L;
struct s_Literal {
    // int     num;
    void    *data;
    void    (*freezer)(t_L *);
};
struct s_Ast {
    t_tag tag;
    union {
        t_O Operator;
        t_L Literal;
        // struct s_Expression {} Espression;
    } u_d;
};

t_Ast   *new_ast_node(t_Ast tree);
t_bool    free_ast_node(t_Ast    **node);
void    asign_resolver(t_O *this);
void    *operate(t_Ast  **this);
void    *solve_ast(t_Ast    *this);
int     *mult(int *a, int *b);
int     *add(int *a, int *b);
#endif