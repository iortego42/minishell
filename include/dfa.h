#ifndef DFA_H
# define DFA_H

# include "libft.h"
# include "libstrings.h"
# define NONE -1

typedef void (*t_Action)(void   *);
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
    SIMPLE,
    DOUBLE,
    QUOTES_NUM
} t_quotes;


typedef enum {
	DONE,
	EMPTY_INPUT,
    WORD_AWAIT,
	OPEN_DOUBLE_QUOTES,
	OPEN_SIMPLE_QUOTES,
	OP_AWAIT,
	REDIR_IN_AWAIT,
	REDIR_OUT_AWAIT,
    HA_AWAIT, // HEREDOC/APPEND AWAIT
    S_B_STR, // SPACE BETWEEN STRINGS 
    S_B_TOK, // SPACE BETWEEN TOKEN
	INVALID_INPUT,
	STATES
} t_state;

typedef struct s_DFA t_DFA;
struct s_DFA {
    size_t  *syms_pos;
    size_t  syms_c;
    t_state state;
    t_state prev_state;
};

typedef enum {
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	EXPAND = 0b1000
} t_redtypes;
typedef struct s_redir
{
	t_string	filename;
	char		type;
} t_redir;

typedef struct s_cmd {
	t_redir		*reds;
	int			reds_c;
	char		expand_mask;
	t_string	cmd;
	//int			pid;
} *t_cmd;

// lexer.c
t_types             which_sym(char token);
t_state             eval_char_pipe(t_DFA *l, char c);
t_bool              eval(t_DFA *l, t_string s);
t_string            *lexer(t_string sentence);
// cmd_lexer.c
t_state				eval_char_red(t_DFA *l, const char c);
size_t				get_filename(t_DFA *l, t_string cur, t_redir *red);
t_redir				get_red(t_DFA *l, t_string   *cur);
void				get_all_reds(t_DFA *l, t_cmd    cmd, t_string   *cur);
t_cmd				get_cmd(t_string strcmd);
// clean.c
void    			clean_red(t_redir *red);
void    			clean_cmd(t_cmd *command);
void    			clean_cmd_list(t_cmd **command_list);
void    			clean_cmd_list_rev(t_cmd **command_list, int i);

const static char	g_state[STATES][SYM_NUM] = {
/*		  
	\s = Space
	\C = Character
	\$ = Variable
	\S = Single Quote
	\D = Double Quote
	\O = Operator
	\< = Redirection In
	\> = Redirection Out
            \s, \$, \S, \D, \O, \<, \>, \C */
	[0]  = { 0,  0,  0,  0,  0,  0,  0,  0}, // DONE
	[1]  = { 1,  2,  3,  4, 11,  6,  7,  2}, // EMPTY_INPUT
	[2]  = { 9,  2,  3,  4,  5,  6,  7,  2}, // WORD_AWAIT
	[3]  = { 3,  3,  9,  3,  3,  3,  3,  3}, // OPEN_SIMPLE_QUOTES
	[4]  = { 4,  4,  4,  9,  4,  4,  4,  4}, // OPEN_DOUBLE_QUOTES
	[5]  = { 5,  2,  3,  4, 11,  6,  7,  2}, // OP_AWAIT
	[6]  = {10,  2,  3,  4, 11,  8, 11,  2}, // REDIR_IN_AWAIT
	[7]  = {10,  2,  3,  4, 11, 11,  8,  2}, // REDIR_OUT_AWAIT
	[8]  = {10,  2,  3,  4, 11, 11, 11,  2}, // HA_AWAIT
	[9]  = { 9,  2,  3,  4,  5,  6,  7,  2}, // S_B_STR
	[10] = {10,  2,  3,  4,  5,  6,  7,  2}, // S_B_TOK
	[11] = {11, 11, 11, 11, 11, 11, 11, 11}, // INVALID_INPUT
};

const static char	*g_alphabets[SYM_NUM] = {
[SPACE] = " \t",
[DOLLAR] = "$",
[SIMPLE_QUOTES] = "'",
[DOUBLE_QUOTES] = "\"",
[OP] = "|",
[REDIN] = "<",
[REDOUT] = ">",
[NON_SYM] = NULL
};
#endif
