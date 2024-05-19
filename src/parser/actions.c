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
// void    pipe_assign(void    *lexer)
// {
//     int index;
//
//     index ((t_DFA *)lexer)->pipes_c--;
//     ((t_DFA *)lexer)->pipes_pos[index] = ;
// }