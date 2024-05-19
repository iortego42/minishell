#include "dfa.h"

void    init_transactions(t_DFA *l)
{
    static void    (*fun[STATES][STATES])(void *);
    t_state        i;

    i = EMPTY_INPUT;
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

void    update_transaction(t_DFA *l, t_state state, void    (*fun)(void *))
{
    t_state i;

    i = EMPTY_INPUT;
    while (i < STATES)
    {
        (*l->transactions)[i][STATES] = fun;
        i++;
    }
}