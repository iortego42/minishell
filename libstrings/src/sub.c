#include "libstrings.h"

t_string    substr_rm(t_string  string, t_string substr)
{
    t_string    cleaned_str;
    t_string    *cleaned_list;

    cleaned_list = split(string, substr);
    if (cleaned_list == NULL)
        return (NULL);
    cleaned_str = lstostr(cleaned_list);
    return (cleaned_str);
}
t_string    p_substr_rm(t_string  string, char *substr)
{
    t_string    cleaned_str;
    t_string    *cleaned_list;

    cleaned_list = p_split(string, substr);
    if (cleaned_list == NULL)
        return (NULL);
    cleaned_str = lstostr(cleaned_list);
    return (cleaned_str);
}

long    substr(t_string string, t_string substr)
{
    size_t  start;
    size_t  substr_l;
    long    substr_pos;

    substr_l = len(substr);
    start = string->start;
    while (string->start < string->end)
    {
        substr_pos = str_ncmp(string, substr, substr_l);
        if (substr_pos < 0)
        {
            substr_pos = string->start;
            string->start = start;
            return (substr_pos);
        }
        string->start++;
    }
    substr_pos = string->start;
    string->start = start;
    if (substr_pos < 0)
        return (substr_pos);
    return (-1);
}

long    p_substr(t_string string, char *substr)
{
    size_t  start;
    size_t  substr_l;
    long    substr_pos;

    substr_l = p_len(substr);
    start = string->start;
    while (string->start < string->end)
    {
        substr_pos = p_str_ncmp(string, substr, substr_l);
        if (substr_pos < 0)
        {
            substr_pos = string->start;
            string->start = start;
            return (substr_pos);
        }
        string->start++;
    }
    substr_pos = string->start;
    string->start = start;
    if (substr_pos < 0)
        return (substr_pos);
    return (-1);
}
