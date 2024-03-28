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
    char s[] = "minishell: error sintáctico cerca del elemento inesperado";

    l->prev_state = l->state;
    l->state = (t_state)g_state[l->state][which_sym(c)];
    if (l->state == INVALID_INPUT)
        printf("%s `%c'\n", s, c);
    else if (l->state == OP_AWAIT && l->prev_state != OP_AWAIT)
        l->pipes_c++;
    return (l->state);
}

t_bool  eval(t_DFA *l, t_string s)
{
    t_string    cur;

    cur = str_cpy(s);
    while (cur->start < cur->end) 
    {
        if (eval_char_pipe(l, get(cur, 0)) == INVALID_INPUT) //should set erno
            return (dtor(&cur), FALSE);
        cur->start++;
    }
    if (l->state >= REDIR_IN_AWAIT)
            return (dtor(&cur), FALSE);
    if (l->pipes_c > 0)
        l->pipes_pos = malloc(sizeof(size_t) * l->pipes_c);
    l->pipes_c = 0;
    cur->start = 0;
    while (cur->start < cur->end)
    {
        eval_char_pipe(l, get(cur, 0));
        if (l->state == OP_AWAIT && l->prev_state != OP_AWAIT)
            l->pipes_pos[l->pipes_c - 1] = cur->start;
        cur->start++;
    }
    dtor(&cur);
    return (TRUE);
}

t_cmd   *get_cmd_list(t_string *pipe_list, t_DFA *l)
{
    t_cmd   *list;
    int     i;

    i = 0;
    list = malloc(sizeof(t_cmd) * (2 + l->pipes_c));
    if (list == NULL)
        return (NULL);
    // printf("%zu - ", l->pipes_c);
    while (pipe_list[i] != NULL)
    {

        list[i] = get_cmd(pipe_list[i], l);
        if (list[i] == NULL)
        {
            clean_cmd_list_rev(&list, --i);
            free(list);
            return (NULL);
        }
        i++;
    }
    // printf("%d\n", i);
    list[i] = NULL;
    return (list);
}

t_cmd   *lexer(t_string sentence)
{
    t_string    *pipe_list;
    t_DFA       l;
    t_bool      is_valid;
    t_cmd       *cmd_list;

    l = (t_DFA){.pipes_pos = NULL, .pipes_c = 0,
    .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT};
    if (sentence == NULL || sentence->data == NULL)
        return (NULL);
    is_valid = eval(&l, sentence);
    if (is_valid)
        pipe_list = nsplit(sentence, l.pipes_c, l.pipes_pos);
    else
        return (NULL);
    if (l.pipes_pos)
        free(l.pipes_pos);
    cmd_list = get_cmd_list(pipe_list, &l);
    if (pipe_list)
        clearlist(&pipe_list);
    return (cmd_list);
}
