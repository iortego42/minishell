# include "dfa.h"

void    sq_count(t_DFA   *l)
{
    l->cmd_p->sq_c++;
}

void    dq_count(t_DFA   *l)
{
    l->cmd_p->dq_c++;
}

void    red_count(t_DFA  *l)
{
    l->cmd_p->reds_c++;
}

void    pipe_count(t_DFA *l)
{
    l->pipes_c++;
}

void    get_pipe_pos(t_DFA *l)
{
    l->pipes_pos[l->pipes_c] = l->cursor->start;
    l->pipes_c++;
}