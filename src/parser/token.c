# include "dfa.h"

// primero se expanden las variables y luego se realiza la sustitucion
// Para splitear por comas o espacios usaremos contadores de quotes con el lexer.
// En el momento que uno incrementa al cambiar de estado implica que nos encontramos ante una string
// Para identificar palabras utilizamos wordawait, ya que al cerrar una comilla seguimos en el estado de word await.
// Para poder dividir correctamente necesitamos primero ubicar donde se encuentran las comillas y luego donde se encuentran las palabras
// t_string    *remove_quotes(t_string cmdstr)
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

/*
 * get_token_list hace uso del cursor del lexer, este debe estar configurado
 * para ser el mismo que el comando (cmd_p->cmd) de modo que get_token_list itera sobre el puntero al comando.
 */
void    add_token(t_token *list, struct s_token token)
{
    while ((*list)->right != NULL)
    {
        (*list) = (*list)->right;
    }
    (*list)->right = malloc(sizeof(struct s_token));
    if ((*list)->right == NULL)
        // return (clear_tokens());
        return (clean_tokens(list));
    *(*list)->right = token;
    (*list)->right->left = list;
}

// comprobar fallos de memoria y segfaults
void    remove_token(t_token *list)
{
    t_token aux;

    if (list NULL || *list == NULL)
        return ;
    aux = (*list);

    if ((*list)->left != NULL)
        (*list)->left->right = (*list)->right;
    else if ((*list)->right != NULL)
        (*list)->right->left = NULL;
    if ((*list)->right != NULL)
        (*list)->right->left = (*list)->left;
    else if ((*list)->left != NULL)
        (*list)->left->right = NULL;
    if ((*list)->left != NULL)
        (*list) = (*list)->left;
    else if ((*list)->right != NULL)
        (*list) = (*list)->right;
    else
        (*list) = NULL;
    dtor(&aux->str);
    free(aux);
}

t_token *get_token_list(t_DFA   *l)
{
    t_token *list;

    // (*l->transactions)[][] = token++;
    eval(l);

}