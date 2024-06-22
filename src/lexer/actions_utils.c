#include "dfa.h"

void init_trans(t_DFA *l) {
    t_state i;

    i = EMPTY_INPUT;
    l->transactions = malloc(sizeof(void (*[STATES][STATES])(t_DFA *)));
    // se debe cambiar a una reserva de memoria unica en la función lexer
    while (i < STATES)
        upd_trans(l, i++, NULL);
    i = EMPTY_INPUT;
    upd_trans_prev_ne(l, REDIR_IN_AWAIT, red_count);
    upd_trans_prev_ne(l, REDIR_OUT_AWAIT, red_count);
    upd_trans_prev_ne(l, OP_AWAIT, pipe_count);
    while (i < STATES) {
        // Gestion de inputs no validos
        (*l->transactions)[INVALID_INPUT][i] = print_error;
        (*l->transactions)[i][INVALID_INPUT] = print_error;
        i++;
    }
}

void upd_trans(t_DFA *l, t_state state, void (*fun)(t_DFA *)) {
    t_state i;

    i = EMPTY_INPUT;
    while (i < STATES) {
        (*l->transactions)[i][state] = fun;
        i++;
    }
}

// update transaction: prev_state not equal
void upd_trans_prev_ne(t_DFA *l, t_state state, void (*fun)(t_DFA *)) {
    t_state i;

    i = EMPTY_INPUT;
    while (i < STATES) {
        (*l->transactions)[i][state] = fun;
        i++;
    }
    (*l->transactions)[state][state] = NULL;
}
