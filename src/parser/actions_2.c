#include "dfa.h"

size_t get_filename(t_DFA *l, t_redir *red)
{
    size_t      end;

    end = 0;
    if (l->state == OPEN_SIMPLE_QUOTES || l->state == OPEN_DOUBLE_QUOTES)
        end++;
    while (l->cursor->start + end < l->cursor->end)
    {
        if (S_B_TOK == eval_char(l, get(l->cursor, end)))
            l->cursor->start++;
        else if (l->state == WORD_AWAIT || l->state == OPEN_SIMPLE_QUOTES
            || l->state == OPEN_DOUBLE_QUOTES)
            end++;
        else if (l->state == S_B_STR)
            break;
        if (!(red->type & EXPAND) && get(l->cursor, end - 2) == '$'
            && (l->state == WORD_AWAIT || l->state == OPEN_DOUBLE_QUOTES))
            red->type |= EXPAND;
    }
    if (l->prev_state == OPEN_SIMPLE_QUOTES
        || l->prev_state == OPEN_DOUBLE_QUOTES)
        end++;
    red->filename = str_ncpy(l->cursor, end);
    return (end);
}

void    get_red(t_DFA *l)
{
    size_t      f_start;
    size_t      f_end;
    t_string    new_cur;
    t_redir     red;

    f_start = l->cursor->start;
    l->cursor->start++; //move cursor to get next state; (cmd |> fn) => (cmd >| fn)
    eval_char(l, get(l->cursor, 0));
    if (l->prev_state == REDIR_IN_AWAIT && l->state == HA_AWAIT)
        (red.type = (char) HEREDOC, l->cursor->start++);
    else if (l->prev_state == REDIR_OUT_AWAIT && l->state == HA_AWAIT)
        (red.type = (char) APPEND, l->cursor->start++);
    else if (l->prev_state == REDIR_OUT_AWAIT && l->state != REDIR_OUT_AWAIT)
        red.type = (char) OUTPUT;
    else if (l->prev_state == REDIR_IN_AWAIT && l->state != REDIR_IN_AWAIT)
        red.type = (char) INPUT;
    // may skip all spaces here
    f_end = get_filename(l, &red) + l->cursor->start;
    l->cursor->start = 0;
    new_cur = str_rmpos(l->cursor, f_start, f_end - 1);  //should protect
    new_cur->start = f_start;
    dtor(&l->cursor);
    l->cursor = new_cur;
    l->cmd_p->reds[l->cmd_p->reds_c] = red;
    l->cmd_p->reds_c++;
}