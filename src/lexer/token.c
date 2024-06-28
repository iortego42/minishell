#include "dfa.h"

// primero se expanden las variables y luego se realiza la sustitucion
// Para splitear por comas o espacios usaremos contadores de quotes con el
// lexer. En el momento que uno incrementa al cambiar de estado implica que nos
// encontramos ante una string Para identificar palabras utilizamos wordawait,
// ya que al cerrar una comilla seguimos en el estado de word await. Para poder
// dividir correctamente necesitamos primero ubicar donde se encuentran las
// comillas y luego donde se encuentran las palabras t_string
// *remove_quotes(t_string cmdstr)
// {
//     t_DFA       l;
//     t_string    *cmdlist;
//     size_t      sq;
//     size_t      dq;
//     size_t      i;
//
//     sq = 0;
//     dq = 0;
//     while (cmdlist)
//     {
//
//     }
//     return (cmdlist);
// }
/*
 * {
 *      string left;
 *      string right;
 *      mark    expand;
 * } token
 *  $variable
 * $ echo $spaces"some  $spaces in dq"$doublequote
 *
 * Se separan las variables en una lista de tokens, que especifican si tienen
 * algo a la izquierda o no.
 *
 */

/* INFO:
 * get_token_list hace uso del cursor del lexer, este debe estar configurado
 * para ser el mismo que el comando (cmd_p->cmd) de modo que get_token_list
 * itera sobre el puntero al comando.
 */
char add_token(t_token *list, struct s_token stoken) {
    t_token token;

    if (list == NULL)
        return (0);
    token = malloc(sizeof(struct s_token));
    if (token == NULL)
        return (FALSE);
    *token = stoken;
    if (*list != NULL && (*list)->right != NULL)
        token->right = (*list)->right;
    else
        token->right = NULL;
    token->left = (*list);
    if (*list != NULL)
        (*list)->right = token;
    (*list) = token;
    return (FALSE);
}

// TODO: comprobar fallos de memoria y segfaults
void remove_token(t_token *list) {
    t_token aux;

    if (list == NULL || *list == NULL)
        return;
    aux = (*list);

    // Enlazamos el lado izquierdo
    if ((*list)->left != NULL)
        (*list)->left->right = (*list)->right;
    else if ((*list)->right != NULL)
        (*list)->right->left = NULL;
    // Enlazamos el lado derecho
    if ((*list)->right != NULL)
        (*list)->right->left = (*list)->left;
    else if ((*list)->left != NULL)
        (*list)->left->right = NULL;
    // Actualizamos la lista
    if ((*list)->left != NULL)
        (*list) = (*list)->left;
    else if ((*list)->right != NULL)
        (*list) = (*list)->right;
    else
        (*list) = NULL;
    dtor(&aux->str);
    free(aux);
}

// El separador es space between words por lo que lo pueddo usar a mi favor para
// saber que tokens se fusionan y cuales no
//
void get_token(t_DFA *l) {
    size_t end;
    t_state status;
    struct s_token token;

    end = 0;
    status = l->state;
    // necesario actualizar la marca en función del estado
    // (comillas dobles, comillas simples o word)
    while (l->cursor->start + end < l->cursor->end) {
        eval_char(l, get(l->cursor, end));
        if (l->prev_state == status && l->state != status)
            break;
        end++;
    }
    token.str = str_ncpy(l->cursor, end);
    if (token.str == NULL)
        // TODO: Limpiar
        // En la llamada a esta función, se debe comprobar errno, si está
        // seteado se debe de borrar toda la información que exista
        return;
    // revisar el -1, puede que no haga falta
    // INFO: Comprobar estado despues de add_token
    add_token(l->cmd_p->tokens, token);
    l->cursor->start += end - 1;
    l->state = status;
}

// INFO: La función get_tokens_list requiere que se hayan generado ya una lista
// del tipo cmd, y por ello el putnero cmd_p apunte a un comando.
// Tampoco se encargará de actualizar el cursor al cursor de comando al que
// apunta cmd_p.
void get_tokens_list(t_DFA *l) {
    l->cmd_p->tokens = malloc(sizeof(t_token *));
    *l->cmd_p->tokens = NULL;
    if (l->cmd_p->tokens == NULL)
        return;
    upd_trans_prev_ne(l, WORD_AWAIT, get_token);
    upd_trans_prev_ne(l, OPEN_SIMPLE_QUOTES, get_token);
    upd_trans_prev_ne(l, OPEN_DOUBLE_QUOTES, get_token);
    // (*l->transactions)[][] = token++;
    eval(l);
}
