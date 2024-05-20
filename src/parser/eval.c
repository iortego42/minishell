#include "dfa.h"

// Globales
const static char	g_state[STATES][SYM_NUM] = {
    /*
        \s = Space
        \C = Character
        \$ = Variable
        \S = Single Quote
        \D = Double Quote
        \O = Operator
        \< = Redirection In
        \> = Redirection Out
        \s, \$, \S, \D, \O, \<, \>, \C */
    [0] = { 0,  0,  0,  0,  0,  0,  0,  0}, // DONE
    [1] = { 1,  2,  3,  4, 11,  6,  7,  2}, // EMPTY_INPUT
    [2] = { 5,  2,  3,  4,  9,  6,  7,  2}, // WORD_AWAIT
    [3] = { 3,  3,  2,  3,  3,  3,  3,  3}, // OPEN_SIMPLE_QUOTES
    [4] = { 4,  4,  4,  2,  4,  4,  4,  4}, // OPEN_DOUBLE_QUOTES
    [5] = { 5,  2,  3,  4,  9,  6,  7,  2}, // S_B_STR
    [6] = {10,  2,  3,  4, 11,  8, 11,  2}, // REDIR_IN_AWAIT
    [7] = {10,  2,  3,  4, 11, 11,  8,  2}, // REDIR_OUT_AWAIT
    [8] = {10,  2,  3,  4, 11, 11, 11,  2}, // HA_AWAIT
    [9] = { 9,  2,  3,  4, 11,  6,  7,  2}, // OP_AWAIT
   [10] = {10,  2,  3,  4,  9,  6,  7,  2}, // S_B_TOK
   [11] = {11, 11, 11, 11, 11, 11, 11, 11}, // INVALID_INPUT
};

const static char	*g_alphabets[SYM_NUM] = {
    [SPACE] = " \t",
    [DOLLAR] = "$",
    [DOUBLE_QUOTES] = "\"",
    [SIMPLE_QUOTES] = "'",
    [OP] = "|",
    [REDIN] = "<",
    [REDOUT] = ">", [NON_SYM] = NULL
};
// Funciones
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

t_state eval_char(t_DFA *l, char c)
{
    l->prev_state = l->state;
    l->state = (t_state)g_state[l->prev_state][which_sym(c)];
    return (l->state);
}

// La nueva versión de eval no limpia el cursor, debe ser eliminado por la
// función que realiza la llamada.
t_bool  eval(t_DFA *l)
{
    while (l->cursor->start < l->cursor->end)
    {
        eval_char(l, get(l->cursor, 0));
        if ((*l->transactions)[l->prev_state][l->state] != NULL)
            (*l->transactions)[l->prev_state][l->state](l);
        if (l->state == INVALID_INPUT) //should set erno
            return (dtor(&l->cursor), FALSE);
        l->cursor->start++;
    }
    if (l->state >= REDIR_IN_AWAIT)
        return (l->cursor->start--, (*l->transactions)[INVALID_INPUT][INVALID_INPUT](l), dtor(&l->cursor), FALSE);
    return (TRUE);
}

void    print_error(t_DFA *l)
{
    // l->cursor->start--;
    printf(
        "minishell: error sintáctico cerca del elemento inesperado `%c'\n",
        get(l->cursor, 0));
}