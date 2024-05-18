#include "dfa.h"

t_state eval_char_red(t_DFA *l, const char c)
{
    char s[] = "minishell: error sintáctico cerca del elemento inesperado";

    l->prev_state = l->state;
    l->state = (t_state) (*l->states)[l->state][which_sym(c)];
    if (l->state == INVALID_INPUT)
        printf("%s `%c'\n", s,c);
    else if ((l->state == REDIR_IN_AWAIT && l->prev_state != REDIR_IN_AWAIT)
        || (l->state == REDIR_OUT_AWAIT && l->prev_state != REDIR_OUT_AWAIT))
        l->reds_c++;
    return (l->state);
}

size_t get_filename(t_DFA *l, t_redir *red)
{
    size_t      end;

    end = 0;
    if (l->state == OPEN_SIMPLE_QUOTES || l->state == OPEN_DOUBLE_QUOTES)
        end++;
    while (l->cursor->start + end < l->cursor->end)
    {
        if (S_B_TOK == eval_char_red(l, get(l->cursor, end)))
            l->cursor->start++;
        else if (l->state == WORD_AWAIT || l->state == OPEN_SIMPLE_QUOTES
            || l->state == OPEN_DOUBLE_QUOTES)
            end++;
        else if (l->state == S_B_STR)
            break;
        if (!(red->type & EXPAND) && get(l->cursor, end - 2) == g_alphabets[DOLLAR][0]
            && (l->state == WORD_AWAIT || l->state == OPEN_DOUBLE_QUOTES))
            red->type |= EXPAND;       
    }
    if (l->prev_state == OPEN_SIMPLE_QUOTES
        || l->prev_state == OPEN_DOUBLE_QUOTES)
        end++;
    red->filename = str_ncpy(l->cursor, end + 1);
    return (end);
}

t_redir get_red(t_DFA *l)
{
    size_t      f_start;
    size_t      f_end;
    t_string    new_cur;
    t_redir     red;
 
    f_start = l->cursor->start;
    l->cursor->start++; //move cursor to get next state; (cmd |> fn) => (cmd >| fn)
    eval_char_red(l, get(l->cursor, 0));
    if (l->state == HA_AWAIT && l->prev_state == REDIR_IN_AWAIT)
        (red.type = (char) HEREDOC, l->cursor->start++);
    else if (l->state == HA_AWAIT && l->prev_state == REDIR_OUT_AWAIT)
        (red.type = (char) APPEND, l->cursor->start++);
    else if (l->state != REDIR_OUT_AWAIT && l->prev_state == REDIR_OUT_AWAIT)
        red.type = (char) OUTPUT;
    if (l->state != REDIR_IN_AWAIT && l->prev_state == REDIR_IN_AWAIT)
        red.type = (char) INPUT;
    // may skip all spaces here
    f_end = get_filename(l, &red) + l->cursor->start;
    l->cursor->start = 0;
    new_cur = str_rmpos(l->cursor, f_start, f_end - 1);  //should protect
    new_cur->start = f_start;
    dtor(&l->cursor);
    l->cursor = new_cur;
    return (red);
}

void get_all_reds(t_DFA *l, t_cmd    cmd)
{
    if (l->reds_c == 0)
        return (cmd->cmd = l->cursor, (void)"");
    cmd->reds = malloc(sizeof(t_redir) * (l->reds_c + 1));
    cmd->cmd = NULL;
    if (cmd->reds == NULL)
        return (dtor(&l->cursor), (void)"");
    l->reds_c = 0;
    while (l->cursor->start < l->cursor->end)
    {
        if (l->reds_c < (eval_char_red(l, get(l->cursor, 0)), l->reds_c))
            cmd->reds[cmd->reds_c++] = get_red(l);
        l->cursor->start++;
    }
    l->cursor->start = 0;
    cmd->cmd = l->cursor;
}

t_cmd   get_cmd(t_string strcmd, t_DFA *l)
{
    t_cmd       cmd;
    const char  (*states)[STATES][SYM_NUM];

    states = l->states;
    *l = (t_DFA){.reds_c = 0, .sq_c = 0, .dq_c = 0,
    .state = EMPTY_INPUT, .prev_state = EMPTY_INPUT, .states = states};
    l->cursor = str_cpy(strcmd);
    cmd = malloc(sizeof(struct s_cmd));
    if (l->cursor == NULL || cmd == NULL)
        return (NULL); 
    while (l->cursor->start < l->cursor->end)
    {
        if (eval_char_red(l, get(l->cursor, 0)) == INVALID_INPUT)
            return (free(cmd), dtor(&l->cursor), NULL);
        l->cursor->start++;
    }
    l->cursor->start = 0;
    get_all_reds(l, cmd);
    // dtor(&l->cursor);
    return (cmd);
}
