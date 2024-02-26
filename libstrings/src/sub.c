#include "libstrings.h"

t_string    substr_rm(t_string  this, t_string substr)
{
    t_string    cleaned_str;
    t_string    *cleaned_list;

    cleaned_list = split(this, substr);
    if (cleaned_list == NULL)
        return (NULL);
    cleaned_str = lstostr(cleaned_list);
    return (cleaned_str);
}
t_string    p_substr_rm(t_string  this, char *substr)
{
    t_string    cleaned_str;
    t_string    *cleaned_list;

    cleaned_list = p_split(this, substr);
    if (cleaned_list == NULL)
        return (NULL);
    cleaned_str = lstostr(cleaned_list);
    return (cleaned_str);
}