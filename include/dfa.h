#ifndef DFA_H
# define DFA_H

# include "minishell.h"
# include "libft.h"
# include "libstrings.h"
# define NONE -1

typedef struct s_DFA t_DFA;
typedef void (*t_Action)(void   *);
typedef enum {
	SPACE,
	DOUBLE_QUOTES,
	SIMPLE_QUOTES,
    OP,
	REDIRECTION,
	DOLLAR,
	NON_SYM,
	SYM_NUM
} t_types;

typedef enum {
    PIPE,
    OUTPUT,
    INPUT,
    OUTPUT_APPEND,
    OPS_NUM
} t_op;

typedef enum {
    SIMPLE,
    DOUBLE,
    QUOTES_NUM
} t_quotes;

typedef struct s_sym {
    t_op        mask;
    int         priority;
    int         pos;
    t_bool      done;
} t_sym;
typedef enum {
	DONE,
	EMPTY_INPUT,
    WORD_AWAIT,
	OPEN_DOUBLE_QUOTES,
	OPEN_SIMPLE_QUOTES,
	OP_AWAIT,
	REDIR_AWAIT,
    S_B_STR, // SPACE BETWEEN STRINGS 
	INVALID_INPUT,
	STATES
} t_state;

struct s_DFA {
    t_Action    action[STATES];
    t_Action    transaction[STATES][STATES];
    char        *alphabets[SYM_NUM];
    t_sym       *syms;
    int         syms_c;
    int         state;
    int         prev_state;
};

const static char	g_state[STATES][SYM_NUM] = {
/*		  
\s = Space
\C = Character
\$ = Variable
\S = Single Quote
\D = Double Quote
\O = Operator
\R = Redirection
          \s,\C,\$,\S,\D,\O,\R */
	[0] = {0, 0, 0, 0, 0, 0, 0}, // DONE
	[1] = {1, 2, 2, 3, 4, 8, 6}, // EMPTY_INPUT
	[2] = {7, 2, 2, 3, 4, 5, 6}, // WORD_AWAIT
	[3] = {3, 3, 3, 7, 3, 3, 3}, // OPEN_SINGLE_QUOTES
	[4] = {4, 4, 4, 4, 7, 4, 4}, // OPEN_DOUBLE_QUOTES
	[5] = {5, 2, 2, 3, 4, 8, 6}, // OP_AWAIT
	[6] = {6, 2, 2, 3, 4, 8, 8}, // REDIR_AWAIT
	[7] = {7, 2, 2, 3, 4, 5, 6}, // S_B_STR
	[8] = {8, 8, 8, 8, 8, 8, 8}, // INVALID_INPUT

};

int             which_alphabet(char    **str, char c);
void            append_sym(int c[2]);
t_types         asign_sym(char mask);
void            sym_count();
void            eval(char  *str);
t_bool          lexer(char  *str);
const static char	*g_alphabets[SYM_NUM] = {
[SPACE] = " \t",
// [QUOTES] = "'\"",
[DOUBLE_QUOTES] = "\"",
[SIMPLE_QUOTES] = "'",
[REDIRECTION] = ">><<",
[OP] = "|",
[DOLLAR] = "$",
};
const static t_sym g_sym[OPS_NUM + 1] = 
{
    [PIPE] = {
        .done = FALSE,
        .priority = 1,
        .pos = -1,
        .mask = PIPE
    },
    [OUTPUT] = {
        .done = FALSE,
        .priority = 1,
        .pos = -1,
        .mask = INPUT
    },
    [INPUT] = {
        .done = FALSE,
        .priority = 1,
        .pos = -1,
        .mask = INPUT
    },
    [OUTPUT_APPEND] = {
        .done = FALSE,
        .priority = 1,
        .pos = -1,
        .mask = OUTPUT_APPEND
    },
    [OPS_NUM] = {
        .mask = (t_op)NONE
    }
};
// Probablemente el unico simbolo necesario sea la pipe
// el resto se parsean dentro del comando.
#endif