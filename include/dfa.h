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
    S_B_STR, // SPACE BETWEEN STRINGS 
	REDIR_IN_AWAIT,
	REDIR_OUT_AWAIT,
    HA_AWAIT, // HEREDOC/APPEND AWAIT
	OP_AWAIT,
    S_B_TOK, // SPACE BETWEEN TOKEN
	INVALID_INPUT,
	STATES
} t_state;

typedef struct s_redir
{
	t_string	filename;
	char		type;
} t_redir;

typedef struct s_cmd {
	t_redir		*reds;
	size_t	    reds_c;
	size_t		sq_c;
	size_t		dq_c;
	char		expand_mask;
	t_string	cmd;
	//int			pid;
} *t_cmd;

typedef struct s_DFA t_DFA;
struct s_DFA {
    size_t 		*pipes_pos;
    size_t 		pipes_c;
    t_state		state;
    t_state		prev_state;
	t_string	cursor;
	t_cmd		cmd_p;
	// muy guay el funcionamiento de la memoria estatica
	void		(*(*transactions)[STATES][STATES])(t_DFA *);
};

typedef enum {
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	EXPAND = 0b1000
} t_redtypes;

// lexer.c
t_cmd		get_cmd(t_string strcmd, t_DFA *l);
t_cmd		*get_cmd_list(t_string *pipe_list, t_DFA *l);
t_string	*get_pipe_list(t_DFA *l);
t_cmd		*lexer(t_string sentence);
// eval.c
t_types		which_sym(char token);
t_state		eval_char(t_DFA *l, char c);
t_bool      eval(t_DFA *l);
void		print_error(t_DFA *l);
// actions.c
// se debe revisar los tipos de las funciones, puede que el compilador suelte errores
// o warnings al intentar compilar por tener la estructura predefinida a
// que reciba un unico argumento de tipo (void *).
void		sq_count(t_DFA *l);
void		dq_count(t_DFA *l);
void		red_count(t_DFA *l);
void		pipe_count(t_DFA *l);
void		get_pipe_pos(t_DFA *l);
// actions_2.c
size_t		get_filename(t_DFA *l, t_redir *red);
void		get_red(t_DFA *l);
// actions_utils.c
void		init_trans(t_DFA *l);
void		upd_trans(t_DFA *l, t_state state, void (*fun)(t_DFA *));
void		upd_trans_prev_ne(t_DFA *l, t_state state, void (*fun)(t_DFA *));
// quotes.c
t_string	*remove_quotes(t_string	cmdstr);

// clean.c void    			clean_red(t_redir *red);
void    	clean_cmd(t_cmd *command);
void    	clean_cmd_list(t_cmd **command_list);
void    	clean_cmd_list_rev(t_cmd **command_list, int i);

#endif