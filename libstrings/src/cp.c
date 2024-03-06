#include "libstrings.h"

t_string	str_cpy(t_string string)
{
	char		*str;
	size_t		i;
	size_t		length;
	t_string	new;

	length = len(string);
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	i = string->start;
	while (i < string->end)
	{
		str[i - string->start] = string->data[i];
		i++;
	}
	str[length] = 0;
	ctor(&new, str);
	free(str);
	return (new);
}

t_string	str_ncpy(t_string string, size_t size)
{
	char		*str;
	size_t		i;
	size_t		length;
	t_string	new;

	i = string->start;
	length = len(string);
	if (length > size)
		length = size;
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	while (i < string->end && (i - string->start) < length)
	{
		str[i - string->start] = string->data[i];
		i++;
	}
	str[length] = 0;
	ctor(&new, str);
	free(str);
	return (new);
}

// void    getfunc_cp(t_string string)
// {
//     string->strcpy = strcpy;
//     string->strncpy = strncpy;
// }
