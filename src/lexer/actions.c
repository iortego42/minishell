#include "dfa.h"

void red_count(t_DFA *l) {
    if (l != NULL && l->cmd_p != NULL)
        l->cmd_p->reds_c++;
}

void pipe_count(t_DFA *l) { l->pipes_c++; }

void get_pipe_pos(t_DFA *l) {
    l->pipes_pos[l->pipes_c] = l->cursor->start;
    l->pipes_c++;
}
