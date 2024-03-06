# include "libstrings.h"

char    get(t_string string, size_t index)
{
    if (string->start + index > string->end)
        return ('\0');
    else
        return (string->data[string->start + index]);
}

char   set(t_string string, size_t index, char value)
{
    if (string->start + index > string->end)
        return ('\0');
    else
    {
        string->data[string->start + index] = value; 
        return (string->data[string->start + index]);
    }
}
