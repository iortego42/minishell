#include "ast.h"

int which_alphabet(char    **str,   char c)
{
    int i;
    int b;
    
    i = 0;
    if (!str || !*str) 
        return -1;
    while (str[i] != NULL)
    {
        b = 0;
        while (str[i][b])
        {
            if (str[i][b] == c)
                return (i);
            b++;
        }
        i++;
    }
    return (i);
}

void    sym_count()
{
    g_sh.lexer.syms_c++;
}

t_types    asign_sym(char mask) {
    t_types var;
    int         len;

    var = 0;
    while (g_sh.lexer.alphabets[var] != NULL)
    {
        if (ft_strchr(g_sh.lexer.alphabets[var], mask))
            return (var);
        var++;
    }
    return NONE;
}

void    eval(char    *str)
{
    int index;
    
    index = 0;
    if (!str) 
        return ;
    while (str[index] != 0)
    {
        g_sh.lexer.state = g_state[g_sh.lexer.state][which_alphabet(g_sh.lexer.alphabets, str[index])];    
        if (g_sh.lexer.action[g_sh.lexer.state])
            g_sh.lexer.action[g_sh.lexer.state](&str[index]);
        if (g_sh.lexer.transaction[g_sh.lexer.prev_state][g_sh.lexer.state])
            g_sh.lexer.transaction[g_sh.lexer.prev_state][g_sh.lexer.state](&str[index]);
        g_sh.lexer.prev_state = g_sh.lexer.state;
        index++;
    }
}

void    append_sym(int c[2])
{
    t_types mask;

    mask = asign_op(c[0]);
    if (mask == NONE)
        return ((void)"42Madrid");
    g_sh.lexer.syms[g_sh.lexer.syms_c] = g_sym[mask];
    g_sh.lexer.syms[g_sh.lexer.syms_c].pos = c[1];
    g_sh.lexer.syms_c++;
}
t_bool    get_syms(char   *str)
// REVISAR
{
    int         c[2];

    c[1] = 0;
    c[0] = str[c[1]];
    g_sh.lexer.state = 0;
    g_sh.lexer.prev_state = 0;
    g_sh.lexer.action[SPACE] = (t_Action)append_sym;
    while(c[0] != 0) 
    {
        g_sh.lexer.state = g_state[g_sh.lexer.state][which_alphabet(g_sh.lexer.alphabet, c[0])];
        if (g_sh.lexer.state == SPACE)
            g_sh.lexer.action[SPACE](c);
        c[1]++;
        c[0] = str[c[1]];
    }
    Data.sym = g_sh.lexer.syms;
    return (TRUE);
}

t_bool	lexer(char    *str)
{
	g_sh.lexer = (t_DFA){ .alphabets = g_alphabets, .prev_state = 0,
		.state = 0, .syms_c = 0, };
    eval(str);
    if (g_sh.lexer.state == INVALID_INPUT)
        return (FALSE);
    g_sh.lexer.syms = malloc(sizeof(t_sym) * (g_sh.lexer.syms_c + 1));
    if (g_sh.lexer.syms == NULL)
        return (FALSE);
    g_sh.lexer.syms[g_sh.lexer.syms_c].mask = NONE;
    g_sh.lexer.syms_c = 0;
    return (get_syms(str));
}
