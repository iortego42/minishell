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
# include "dfa.h"
# include "minishell.h"
# include "libft.h"

# define NEW_AST(tag, ...)\
        new_ast_node((t_Ast){tag, {.tag=(struct s_ ## tag){__VA_ARGS__}}})
# define AST_SWITCH(tag, ...)\
        (t_Ast){tag, {.tag=(struct s_ ## tag){__VA_ARGS__}}}
# define GET_RESOLVER(op)\
        op.Resolve = g_resolver[op.mask]
# define MAX_PRIORITY 4
typedef void *(*t_Resolver)(void *, void *);
typedef struct s_Ast t_Ast;
typedef enum {
    Operator,
    Literal,
    Command,
    Expression
} t_tag;
typedef struct s_Operator t_O;
struct s_Operator {
    t_Ast   *left;
    t_Ast   *right;
    t_types mask;
    int     pos;
    t_Resolver Resolve;
};
typedef struct s_Literal t_L;
struct s_Literal {
    void    *data;
    void    (*freezer)(t_L *);
};
typedef struct s_Command t_C;
struct s_Command {
    int     start;
    int     end;
    int     pid;
    
};
typedef struct s_Expression t_E;
struct s_Expression {
    int     start;
    int     end;
};
struct s_Ast {
    t_tag tag;
    union {
        t_O Operator;
        t_L Literal;
        t_C Command;
        t_E Expression;
    } u_d;
};


typedef struct s_data {
    t_Ast   *tree;
    char    *cmd;
    t_sym   *sym;
} t_data;
t_data Data;


void            constructor(t_Ast   *this);
void            to_operator(t_Ast   *this, t_sym    op);
void            to_literal(t_Ast    *this);
t_Ast           *new_ast_node(t_Ast tree);
t_bool          free_ast_node(t_Ast    **node);
void            *operate(t_Ast  **this);
void            *solve_ast(t_Ast    *this);
const static t_Resolver g_resolver[SYM_NUM + 1] = {
   [SYM_NUM] = NULL
};

#endif