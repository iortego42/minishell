#include "libstrings.h"

t_string				str_joinfront(t_string string, t_string preffix)
{
    size_t      length;
    size_t      i;
    t_string    new;
    char        *data;

    new = str_cpy(string);
    if (new == NULL)
        return (new);
    length = len(new) + len(preffix);
    data = malloc(length * 1);
    if (!data)
        return (NULL);
    i = preffix->start;
    while (i++ < preffix->end)
        data[i - 1] = preffix->data[i - 1];
    i = new->start;
    while (i++ < new->end)
        data[i + preffix->end - 1] = new->data[i - 1];
    free(new->data);
    new->data = data;
    new->data_len = length;
    new->end = length;
    return (new);
}

t_string				p_str_joinfront(t_string string, char *preffix)
{
    size_t      length;
    size_t      i;
    size_t      new_i;
    t_string    new;
    char        *data;

    new = str_cpy(string);
    if (new == NULL)
        return (new);
    length = len(new) + p_len(preffix);
    data = malloc(length * 1);
    if (!data)
        return (NULL);
    i = 0;
    while (preffix[i++])
        data[i - 1] = preffix[i - 1]; 
    i--;
    new_i = new->start;
    while (new_i++ < new->end)
        data[new_i + i - 1] = new->data[new_i - 1];
    free(new->data);
    new->data = data;
    new->data_len = length;
    new->end = length;
    return (new);
}

t_string				str_joinback(t_string string, t_string suffix)
{
    size_t      length;
    size_t      i;
    t_string    new;
    char        *data;

    new = str_cpy(string);
    if (new == NULL)
        return (new);
    length = len(new) + len(suffix);
    data = malloc(length * 1);
    if (!data)
        return (NULL);
    i = new->start;
    while (i++ < new->end)
        data[i - 1] = new->data[i - 1];
    i = suffix->start;
    while (i++ < suffix->end)
        data[i + new->end - 1] = suffix->data[i - 1];
    free(new->data);
    new->data = data;
    new->data_len = length;
    new->end = length;
    return (new);
}

t_string				p_str_joinback(t_string string, char *suffix)
{
    size_t      length;
    size_t      i;
    t_string    new;
    char        *data;

    new = str_cpy(string);
    if (new == NULL)
        return (new);
    length = len(new) + p_len(suffix);
    data = malloc(length * 1);
    if (!data)
        return (NULL);
    i = new->start;
    while (i++ < new->end)
        data[i - 1] = new->data[i - 1];
    i = 0;
    while (suffix[i++])
        data[i + new->end - 1] = suffix[i - 1];
    free(new->data);
    new->data = data;
    new->data_len = length;
    new->end = length;
    return (new);
}