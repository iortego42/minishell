#include "dfa.h"

t_bool init_actions(t_DFA *l)
{
    static void    (*fun[STATES][STATES])(void *);
    t_state        i;

    i = DONE;
    while (i < STATES)
    {
        fun[i][REDIR_IN_AWAIT] = red_count;
        fun[i][REDIR_OUT_AWAIT] = red_count;
        fun[i][OP_AWAIT] = pipe_count;
        fun[i][SIMPLE_QUOTES] = sq_count;
        fun[i][DOUBLE_QUOTES] = dq_count;
        // Gestion de inputs no validos
        // fun[INVALID_INPUT][i] = print_error;
        // fun[i][INVALID_INPUT] = print_error;
    }
    l->transactions = &fun;
}