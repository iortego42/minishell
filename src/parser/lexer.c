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
        l->syms_c++;
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
    if (l->syms_c > 0)
        l->syms_pos = malloc(sizeof(size_t) * l->syms_c);
    l->syms_c = 0;
    cur->start = 0;
    while (cur->start < cur->end)
    {
        eval_char_pipe(l, get(cur, 0));
        if (l->state == OP_AWAIT && l->prev_state != OP_AWAIT)
            l->syms_pos[l->syms_c - 1] = cur->start;
        cur->start++;
    }
    dtor(&cur);
    return (TRUE);
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
