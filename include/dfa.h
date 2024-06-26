#ifndef DFA_H
#define DFA_H

#include "libft.h"
#include "libstrings.h"
#include "minishell.h"
#define NONE -1

#define RIGHT_SIBLING 0b10
#define SPLIT 0b100
#define EXPAND 0b1000

typedef enum {
    SPACE,
    DOLLAR,
    DOUBLE_QUOTES,
    SIMPLE_QUOTES,
    OP,
    REDIN,
    REDOUT,
    NON_SYM,
    SYM_NUM
} t_types;

typedef enum {
    DONE,
    EMPTY_INPUT,
    WORD_AWAIT,
    OPEN_DOUBLE_QUOTES,
    OPEN_SIMPLE_QUOTES,
    S_B_STR, // SPACE BETWEEN STRINGS
    REDIR_IN_AWAIT,
    REDIR_OUT_AWAIT,
    HA_AWAIT, // HEREDOC/APPEND AWAIT
    OP_AWAIT,
    S_B_TOK, // SPACE BETWEEN TOKEN
    INVALID_INPUT,
    STATES
} t_state;

typedef struct s_redir {
    t_string filename;
    // comprobar en ejecución que si el nombre tiene un espacio devolver un
    // error
    char type;
} t_redir;

typedef struct s_token *t_token;
struct s_token {
    t_token left;
    t_token right;
    t_string str;
    char type;
};

typedef struct s_cmd {
    t_redir *reds;
    size_t reds_c;
    char expand_mask;
    t_string cmd;
    t_token *tokens;
    /* hay que realizar split cuando:
     * WORD_AWAIT && S_B_STR
     * WORD_AWAIT && REDIR_IN_AWAIT
     * WORD_AWAIT && REDIR_OUT_AWAIT
     *
     * para ello nos guardamos en dichos casos las posiciones, ya que al
     * sustituir y quitar las comillas sera imposible ver las separaciones con
     * claridad. El array tokens contiene las palabras sin sustituir ni expandir
     * las variables Primero expandimos tokens que no tengan comillas dobles,
     * comprobamos si se puede splitear y luego quitamos las comillas y
     * expandimos de nuevo.
     */
    t_string *parsed;
    // int			pid;
    int std_in;
    int std_out;
} *t_cmd;

typedef struct s_DFA t_DFA;
struct s_DFA {
    size_t *pipes_pos;
    size_t pipes_c;
    t_state state;
    t_state prev_state;
    t_string cursor;
    // INFO: cmd_p es un puntero al comando que se está analizando en este
    // momento. ej: l->cmd_p == l->commands[2]
    t_cmd cmd_p;
    void (*(*transactions)[STATES][STATES])(t_DFA *);
    t_cmd *commands;
};

typedef enum { INPUT, OUTPUT, APPEND, HEREDOC } t_redtypes;
// lexer.c
t_cmd get_cmd(t_string strcmd, t_DFA *l);
t_cmd *get_cmd_list(t_string *pipe_list, t_DFA *l);
t_string *get_pipe_list(t_DFA *l);
t_cmd *lexer(t_string sentence);
// eval.c
t_types which_sym(char token);
t_state eval_char(t_DFA *l, char c);
t_bool eval(t_DFA *l);
void print_error(t_DFA *l);
// actions.c
// se debe revisar los tipos de las funciones, puede que el compilador suelte
// errores o warnings al intentar compilar por tener la estructura predefinida a
// que reciba un unico argumento de tipo (void *).
void red_count(t_DFA *l);
void pipe_count(t_DFA *l);
void get_pipe_pos(t_DFA *l);
// actions_2.c
size_t get_filename(t_DFA *l, t_redir *red);
void get_red(t_DFA *l);
void get_word(t_DFA *l);
// actions_utils.c
void init_trans(t_DFA *l);
void upd_trans(t_DFA *l, t_state state, void (*fun)(t_DFA *));
void upd_trans_prev_ne(t_DFA *l, t_state state, void (*fun)(t_DFA *));
// token.c
void get_tokens_list(t_DFA *l);
void get_token(t_DFA *l);
void remove_token(t_token *list);
char add_token(t_token *list, struct s_token stoken);

// clean.c void    			clean_red(t_redir *red);
void clean_cmd(t_cmd *command);
void clean_cmd_list(t_cmd **command_list);
void clean_cmd_list_rev(t_cmd **command_list, int i);
void clean_tokens(t_token *list);

#endif
