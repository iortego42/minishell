#include "ast.h"
// metodo de la lista de la compra:
//
//
// creamos un array inicial con el que comparamos los 
// items que se encuentran procesados y los que no. 
// para ello recorremos la string hasta el token que no
// ha sido procesado.
//
// Despues se llama de forma recursiva al constructor
// añadiendo antes el token encontrado a la lista.
// de este modo se recorre la string y se procesan todos
// los tokens hasta llegar a los literales.
//
//
// Idea principal, todo se trata como un comando a ejecutar
// si se encuentra algun token se ejecuta lo que el toquen
// necesite (se resuelve el token) y se continua con el
// trabajo.


void    to_operator(t_Ast   *this, t_sym    op)
{
    int     l_start;
    int     l_end;
    int     r_start;
    int     r_end;

    if (this->tag != Expression)
        return ;
    l_start = this->u_d.Expression.start;
    l_end = op.pos; // revisar posiciones
    r_start = op.pos + 1;
    r_end = this->u_d.Expression.end;
    this->u_d.Operator.left = AST_NODE(Expression, l_start, l_end);
    this->u_d.Operator.right = AST_NODE(Expression, r_start, r_end);
    this->u_d.Operator.mask = op.mask;
    this->u_d.Operator.pos = op.pos;
    this->tag = Operator;
    GET_RESOLVER(this->u_d.Operator);
}

void    to_literal(t_Ast    *this)
{
    char    *num_str;
    t_string str;
    int     len;


}
void    constructor(t_Ast  *this)
{
    int i;
    int prior;

    if (this->tag != Expression)
        return (void)"42Madrid";
    prior = 1;
    while (prior < MAX_PRIORITY)
    {
        i = 0;
        while (g_sh.sym[i].mask != NONE)
            i++;
        while (i-- > 0)
        {
            if (g_sh.sym[i].priority == prior && !g_sh.sym[i].done
                && g_sh.sym[i].pos < this->u_d.Expression.end
                && g_sh.sym[i].pos > this->u_d.Expression.start)
            {
                to_operator(this, g_sh.sym[i]);
                g_sh.sym[i].done = TRUE;
                return ;
            }
        }
        prior++;
    }
    to_literal(this);
}
