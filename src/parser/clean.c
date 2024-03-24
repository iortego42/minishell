#include "dfa.h"

void    clean_red(t_redir *red)
{
    dtor(&red->filename);
}
void    clean_cmd(t_cmd *command)
{
    int i;

    i = 0;
    dtor(&(*command)->cmd);
    if ((*command)->reds)
    {
        while (i < (*command)->reds_c)
            clean_red(&(*command)->reds[i++]);
        free((*command)->reds);
        (*command)->reds = NULL;
    }
    free(*command);
    *command = NULL;
}

void    clean_cmd_list(t_cmd **command_list)
{
    int i;

    i = 0;
    while ((*command_list)[i])
        clean_cmd(&(*command_list)[i++]);
    free(*command_list);
    *command_list = NULL;
}

void    clean_cmd_list_rev(t_cmd **command_list, int i)
{
    while (i >= 0)
        clean_cmd(&(*command_list)[i--]);
    free(*command_list);
    *command_list = NULL;
}