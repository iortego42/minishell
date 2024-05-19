# include "dfa.h"

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

    l = (t_DFA){.pipes_pos = NULL, .pipes_c = 0, .cursor = str_cpy(sentence),
    .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT};
    if (sentence == NULL || sentence->data == NULL)
        return (NULL);
    is_valid = eval(&l);
    dtor(&l.cursor);
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
