# include "dfa.h"

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

t_state eval_char_pipe(t_DFA *l, char c)
{
    l->prev_state = l->state;
    l->state = (t_state)g_state[l->state][which_sym(c)];
    if (l->state == INVALID_INPUT)
        syntax_error();
    else if (l->state == OP_AWAIT && l->prev_state != OP_AWAIT)
        l->syms_c++;
    return (l->state);
}

void    syntax_error(void)
{
    char    message[] = "minishell: error sintáctico.\n";

    write(2, message, p_len(message));
}

t_bool  eval(t_DFA *l, t_string s)
{
    t_string    cursor;

    cursor = str_cpy(s);
    while (cursor->start < cursor->end) 
    {
        if (eval_char(l, get(cursor, 0)) == INVALID_INPUT) //should set erno
            return (dtor(&cursor), FALSE);
        cursor->start++;
    }
    if (l->syms_c > 0)
        l->syms_pos = malloc(sizeof(size_t) * l->syms_c);
    l->syms_c = 0;
    cursor->start = 0;
    while (cursor->start < cursor->end)
    {
        eval_char(l, get(cursor, 0));
        if (l->state == OP_AWAIT && l->prev_state != OP_AWAIT)
            l->syms_pos[l->syms_c - 1] = cursor->start;
        cursor->start++;
    }
    dtor(&cursor);
    return (TRUE);
}

t_state eval_char_red(t_DFA *l, const char c)
{
    l->prev_state = l->state;
    l->state = (t_state) g_state[l->state][which_sym(c)];
    if (l->state == INVALID_INPUT)
        syntax_error();
    else if ((l->state == REDIR_IN_AWAIT && l->prev_state != REDIR_IN_AWAIT)
        || (l->state == REDIR_OUT_AWAIT && l->prev_state != REDIR_OUT_AWAIT))
        l->syms_c++;
    return (l->state);
}

t_cmd   *getcmd(t_string strcmd)
{
    t_cmd       *cmd;
    t_string    cursor;
    t_DFA       l;

    l = (t_DFA){.syms_pos = NULL, .syms_c = 0, .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT};
    cursor = str_cpy(strcmd);
    cmd = malloc(sizeof(t_cmd));
    if (cursor == NULL || cmd == NULL)
        return (NULL);
    
    // get index of redirections in string
    while (cursor->start < cursor->end)
    {
        if (eval_char_red(&l, get(cursor, 0)) == INVALID_INPUT) //should set erno
            return (free(cmd), dtor(&cursor), FALSE);
        cursor->start++;
// Make a function which lets the lexer sym counter increment by 1
// also set the possition of the redirection, then trim it from 
// may be start could help us to get that
    }
    cursor->start = 0;
    cmd->reds = malloc(sizeof(t_string) * (l.syms_c + 1));
    if (cmd->reds == NULL)
        return (free(cmd), dtor(&cursor), NULL);
    // fill redirections array and remove them from cmd string
    {
        //found redirection;
        // copy redirection to string array;
        // remove redirection string from array;
    }
    // ctor();

}

t_string    *lexer(t_string sentence)
{
    t_string    *pipe_list;
    t_DFA       l;
    t_bool      is_valid;

    l = (t_DFA){.syms_pos = NULL, .syms_c = 0, .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT};
    if (sentence == NULL || sentence->data == NULL)
        return (NULL);
    is_valid = eval(&l, sentence);
    if (is_valid)
        pipe_list = nsplit(sentence, l.syms_c, l.syms_pos);
    else
        pipe_list = NULL;
    if (l.syms_pos)
        free(l.syms_pos);
    return (pipe_list);
}
