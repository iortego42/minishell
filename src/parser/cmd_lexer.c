#include "dfa.h"

t_state eval_char_red(t_DFA *l, const char c)
{
    char s[] = "minishell: error sintáctico cerca del elemento inesperado";

    l->prev_state = l->state;
    l->state = (t_state) g_state[l->state][which_sym(c)];
    if (l->state == INVALID_INPUT)
        printf("%s `%c'\n", s,c);
    else if ((l->state == REDIR_IN_AWAIT && l->prev_state != REDIR_IN_AWAIT)
        || (l->state == REDIR_OUT_AWAIT && l->prev_state != REDIR_OUT_AWAIT))
        l->syms_c++;
    return (l->state);
}

// This function should get the file name,
// TIP: use the lexer to identify where does the quotes end.
// pass reference to Red struct and bitOR the EXPAND flag if $ 
// is fetched.
// also should check char
size_t get_filename(t_DFA *l, t_string cur, t_redir *red)
{
    size_t      end;

    end = 0;
    if (l->state == OPEN_SIMPLE_QUOTES || l->state == OPEN_DOUBLE_QUOTES)
        end++;
    while (cur->start + end < cur->end)
    {
        if (S_B_TOK == eval_char_red(l, get(cur, end)))
            cur->start++;
        else if (l->state == WORD_AWAIT || l->state == OPEN_SIMPLE_QUOTES
            || l->state == OPEN_DOUBLE_QUOTES)
            end++;
        else if (l->state == S_B_STR)
            break;
        if (!(red->type & EXPAND) && get(cur, end - 2) == g_alphabets[DOLLAR][0] 
            && (l->state == WORD_AWAIT || l->state == OPEN_DOUBLE_QUOTES))
            red->type |= EXPAND;       
    }
    if (l->prev_state == OPEN_SIMPLE_QUOTES
        || l->prev_state == OPEN_DOUBLE_QUOTES)
        end++;
    red->filename = str_ncpy(cur, end + 1);
    return (end);
}

t_redir get_red(t_DFA *l, t_string   *cur)
{
    size_t      f_start;
    size_t      f_end;
    t_string    new_cur;
    t_redir     red;
 
    f_start = (*cur)->start;
    (*cur)->start++; //move cursor to get next state; (cmd |> fn) => (cmd >| fn)
    eval_char_red(l, get((*cur), 0)); 
    if (l->state == HA_AWAIT && l->prev_state == REDIR_IN_AWAIT)
        (red.type = (char) HEREDOC, (*cur)->start++);
    else if (l->state == HA_AWAIT && l->prev_state == REDIR_OUT_AWAIT)
        (red.type = (char) APPEND, (*cur)->start++);
    else if (l->state != REDIR_OUT_AWAIT && l->prev_state == REDIR_OUT_AWAIT)
        red.type = (char) OUTPUT;
    if (l->state != REDIR_IN_AWAIT && l->prev_state == REDIR_IN_AWAIT)
        red.type = (char) INPUT;
    // may skip all spaces here
    f_end = get_filename(l, (*cur), &red) + (*cur)->start;
    (*cur)->start = 0;
    new_cur = str_rmpos((*cur), f_start, f_end - 1);  //should protect
    new_cur->start = f_start;
    dtor(cur);
    (*cur) = new_cur;
    return (red);
}

void get_all_reds(t_DFA *l, t_cmd    cmd, t_string   *cur)
{
    
    if (l->syms_c == 0)
        return ;
    cmd->reds = malloc(sizeof(t_redir) * (l->syms_c + 1));
    if (cmd->reds == NULL)
        return ;
    l->syms_c = 0;
    while ((*cur)->start < (*cur)->end)
    {
        if (l->syms_c < (eval_char_red(l, get(*cur, 0)), l->syms_c))
            cmd->reds[cmd->reds_c++] = get_red(l, cur);
        (*cur)->start++;
    }
    (*cur)->start = 0;
    cmd->cmd = *cur;
}

t_cmd   get_cmd(t_string strcmd)
{
    t_cmd       cmd;
    t_string    cur;
    t_DFA       l;

    l = (t_DFA){.syms_pos = NULL, .syms_c = 0, .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT};
    cur = str_cpy(strcmd);
    cmd = malloc(sizeof(struct s_cmd));
    if (cur == NULL || cmd == NULL)
        return (NULL); 
    while (cur->start < cur->end)
    {
        if (eval_char_red(&l, get(cur, 0)) == INVALID_INPUT) 
            return (free(cmd), dtor(&cur), NULL);
        cur->start++;
    }
    cur->start = 0;
    get_all_reds(&l, cmd, &cur);
    // dtor(&cur);
    return (cmd);
}
