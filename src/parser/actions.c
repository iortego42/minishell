# include "dfa.h"

void    sq_count(t_DFA   *lexer)
{
    lexer->sq_c++;
}

void    dq_count(t_DFA   *lexer)
{
    lexer->dq_c++;
}

void    red_count(t_DFA  *lexer)
{
    lexer->reds_c++;
}

void    pipe_count(t_DFA *lexer)
{
    lexer->pipes_c++;
}

void    get_pipe_pos(t_DFA *lexer)
{
    lexer->pipes_pos[lexer->pipes_c] = lexer->cursor->start;
    lexer->pipes_c++;
}