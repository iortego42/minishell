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
	DOLLAR,
    OP,
	REDIN,
	REDOUT,
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
	REDIR_IN_AWAIT,
	REDIR_OUT_AWAIT,
    FILE_AWAIT, // HEREDOC/APPEND AWAIT
    S_B_STR, // SPACE BETWEEN STRINGS 
    S_B_TOK, // SPACE BETWEEN TOKEN
	INVALID_INPUT,
	STATES
} t_state;

struct s_DFA {
    size_t  *syms_pos;
    size_t  syms_c;
    t_state state;
    t_state prev_state;
};

// const static char	g_state[STATES][SYM_NUM] = {
// /*		  
// \s = Space
// \C = Character
// \$ = Variable
// \S = Single Quote
// \D = Double Quote
// \O = Operator
// \< = Redirection In
// \> = Redirection Out
//             \s, \$, \S, \D, \O, \<, \>, \C */
// 	[0]  = { 0,  0,  0,  0,  0,  0,  0,  0}, // DONE
// 	[1]  = { 1,  2,  3,  4, 11,  6,  7,  2}, // EMPTY_INPUT
// 	[2]  = { 9,  2,  3,  4,  5,  6,  7,  2}, // WORD_AWAIT
// 	[3]  = { 3,  3,  9,  3,  3,  3,  3,  3}, // OPEN_SINGLE_QUOTES
// 	[4]  = { 4,  4,  4,  9,  4,  4,  4,  4}, // OPEN_DOUBLE_QUOTES
// 	[5]  = { 5,  2,  3,  4, 11,  6,  7,  2}, // OP_AWAIT
// 	[6]  = {10,  2,  3,  4, 11,  8, 11,  2}, // REDIR_IN_AWAIT
// 	[7]  = {10,  2,  3,  4, 11, 11,  8,  2}, // REDIR_OUT_AWAIT
// 	[8]  = {10,  9,  9,  9,  9,  9,  9,  9}, // HA_AWAIT
// 	[9]  = { 9,  2,  3,  4,  5,  6,  7,  2}, // S_B_STR
// 	[10] = {10,  2,  3,  4,  5,  6,  7,  2}, // S_B_TOK
// 	[11] = {11, 11, 11, 11, 11, 11, 11, 11}, // INVALID_INPUT

// };

t_types             which_sym(char token);
t_state             eval_char(t_DFA l, char c);
void                syntax_error(void);
t_bool              eval(t_DFA l, t_string s);
t_string            *lexer(t_string sentence);
// const static char	*g_alphabets[SYM_NUM] = {
// [SPACE] = " \t",
// [DOLLAR] = "$",
// // [QUOTES] = "'\"",
// [SIMPLE_QUOTES] = "'",
// [DOUBLE_QUOTES] = "\"",
// [OP] = "|",
// [REDIN] = "<",
// [REDOUT] = ">",
// [NON_SYM] = NULL
// };

#endif
