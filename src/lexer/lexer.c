# include "dfa.h"

t_cmd get_cmd(t_string strcmd, t_DFA *l)
{
    t_cmd   cmd;

    cmd = malloc(sizeof(struct s_cmd));
    if (cmd == NULL)
        return (NULL);
    *l = (t_DFA){.cmd_p = cmd, .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT,
        .cursor = str_cpy(strcmd)};
    init_trans(l);
    eval(l);
    cmd->reds = malloc(sizeof(t_redir) * (cmd->reds_c + 1));
    cmd->reds_c = 0;
    if (cmd->reds == NULL)
        return (dtor(&l->cursor), free(cmd), l->cmd_p = NULL, NULL);
    cmd->cmd = NULL;
    // En la segunda evaluación se deberan recopilar tanto las comillas como
    // las diferentes variables establecidas por el usuario
    upd_trans_prev_ne(l, REDIR_IN_AWAIT, get_red);
    upd_trans_prev_ne(l, REDIR_OUT_AWAIT, get_red);
    l->cursor->start = 0;
    eval(l);
    l->cursor->start = 0;
    cmd->cmd = l->cursor;
    free(l->transactions);
    return (cmd);
}

t_string    *get_pipe_list(t_DFA *l)
{
    t_string    *pipe_list;

    if (eval(l) == FALSE)
        return (NULL);
    if (l->pipes_c > 0)
        l->pipes_pos = malloc(sizeof(size_t) * l->pipes_c);
    l->pipes_c = 0;
    upd_trans_prev_ne(l, OP_AWAIT, get_pipe_pos);
    l->cursor->start = 0;
/*
 * ORDEN DE PARSEO
 * 1. Obtención de las pipes
 * 2. Recopilación de las redirecciones
 * 3. Comillas y tokenización
 * 4. Expansión de variables
 * 5. Separación en palabras y eliminación de las comillas (tiene que suceder simultaneamente)
 */
    eval(l);
    pipe_list = nsplit(l->cursor, l->pipes_c, l->pipes_pos);
    if (l->pipes_pos)
        free(l->pipes_pos);
    return (pipe_list);
}

t_cmd   *get_cmd_list(t_string *pipe_list, t_DFA *l)
{
    t_cmd   *list;
    int     i;

    i = 0;
    list = malloc(sizeof(t_cmd) * (2 + l->pipes_c));
    if (list == NULL)
        return (NULL);
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
    list[i] = NULL;
    return (list);
}

t_cmd   *lexer(t_string sentence)
{
    t_string    *pipe_list;
    t_DFA       l;
    t_cmd       *cmd_list;

    l = (t_DFA){.pipes_pos = NULL, .pipes_c = 0, .cursor = str_cpy(sentence),
    .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT};
    init_trans(&l);
    if (sentence == NULL || sentence->data == NULL)
        return (NULL);
    pipe_list = get_pipe_list(&l);
    dtor(&l.cursor);
    free(l.transactions);
    if (pipe_list == NULL)
        return (NULL);
    cmd_list = get_cmd_list(pipe_list, &l);
    if (pipe_list)
        clearlist(&pipe_list);
    return (cmd_list);
}
