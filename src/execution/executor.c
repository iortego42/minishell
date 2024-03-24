# include "executor.h"

// void    single_exec(t_string    *cmd)
// {
//     char    **args;
//     args = strlstocharls(cmd);
//     if (!args)
//         return ;
//     execve()
// }

// char    *check_path(const char  *cmd, const char **path)
// {
//     char    *routes;
//     int     i;

//     i = 0;
//     get_env();
//     if (cmd[0] == '/' || cmd[0] == '.')
//         access(cmd, R_OK | X_OK);
//     else
//     {
//         routes
//         while (routes && routes[i] != 0)
//         {

//         }
//     }
// }

t_string    eval_redirs(t_string    *cmd)
{
    t_DFA       l;
    t_string    cursor;

    cursor = str_cpy(cmd);
    if (!cursor)
        return (NULL);
    l = (t_DFA){.syms_pos = NULL, .syms_c = 0, .state = 1, .prev_state = 1};
    while ()
    {
        
    }
}

// t_bool  executor(t_string   *pipe_list)
// {
//     int i;

//     while (pipe_list[i])
//     {

//     }
// }
