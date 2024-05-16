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
