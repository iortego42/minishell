#include "dfa.h"

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