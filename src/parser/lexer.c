# include "dfa.h"


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
	[3]  = { 3,  3,  9,  3,  3,  3,  3,  3}, // OPEN_SINGLE_QUOTES
	[4]  = { 4,  4,  4,  9,  4,  4,  4,  4}, // OPEN_DOUBLE_QUOTES
	[5]  = { 5,  2,  3,  4, 11,  6,  7,  2}, // OP_AWAIT
	[6]  = {10,  2,  3,  4, 11,  8, 11,  2}, // REDIR_IN_AWAIT
	[7]  = {10,  2,  3,  4, 11, 11,  8,  2}, // REDIR_OUT_AWAIT
	[8]  = {10,  9,  9,  9,  9,  9,  9,  9}, // HA_AWAIT
	[9]  = { 9,  2,  3,  4,  5,  6,  7,  2}, // S_B_STR
	[10] = {10,  2,  3,  4,  5,  6,  7,  2}, // S_B_TOK
	[11] = {11, 11, 11, 11, 11, 11, 11, 11}, // INVALID_INPUT

};

const static char	*g_alphabets[SYM_NUM] = {
[SPACE] = " \t",
[DOLLAR] = "$",
// [QUOTES] = "'\"",
[SIMPLE_QUOTES] = "'",
[DOUBLE_QUOTES] = "\"",
[OP] = "|",
[REDIN] = "<",
[REDOUT] = ">",
[NON_SYM] = NULL
};





t_types which_sym(char token)
{
    t_types i;
    int char_i;

    i = SPACE;
    char_i = 0;
    while (g_alphabets[i] != NULL)
    {
        if (token == g_alphabets[i][char_i])
            return (i);
        i++;
    }
    return (NON_SYM);
}

t_state eval_char(t_DFA l, char c)
{
    l.prev_state = l.state;
    l.state = (t_state)g_state[l.state][which_sym(c)];
    if (l.state == INVALID_INPUT)
        syntax_error();
    return (l.state);
}

void    syntax_error(void)
{
    char    message[] = "minishell: error sintáctico.\n";

    write(2, message, p_len(message));
}

t_bool  eval(t_DFA l, t_string s)
{
    t_string    cursor;

    cursor = str_cpy(s);
    while (cursor->start < cursor->end) 
    {
        eval_char(l, get(cursor, 0));
        if (l.state == OP_AWAIT)
            l.syms_c++;
        else if (l.state == INVALID_INPUT) //should set erno
            return (dtor(&cursor), FALSE);
        cursor->start++;
    }
    l.syms_pos = malloc(sizeof(int) * l.syms_c);
    l.syms_c = 0;
    while (cursor->start < cursor->end)
        if (eval_char(l, get(cursor, 0)) == OP_AWAIT)
            l.syms_pos[l.syms_c++] = cursor->start;
    dtor(&cursor);
    return (TRUE);
}

t_string    *lexer(t_string sentence)
{
    t_string    *pipe_list;
    t_DFA       l;

    l = (t_DFA){NULL, 0, 0, 0};
    if (!eval(l, sentence))
        return (NULL);
    pipe_list = nsplit(sentence, l.syms_c, l.syms_pos);
    if (pipe_list == NULL)
        return (NULL);
    return (pipe_list);
}
