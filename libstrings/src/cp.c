#include "libstrings.h"

t_string	str_cpy(t_string this)
{
	char		*str;
	size_t		i;
	size_t		length;
	t_string	new;

	length = len(this);
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	i = this->start;
	while (i < this->end)
	{
		str[i - this->start] = this->data[i];
		i++;
	}
	str[length] = 0;
	ctor(&new, str);
	free(str);
	return (new);
}

t_string	str_ncpy(t_string this, size_t size)
{
	char		*str;
	size_t		i;
	size_t		length;
	t_string	new;

	i = this->start;
	length = len(this);
	if (length > size)
		length = size;
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	while (i < this->end && (i - this->start) < length)
	{
		str[i - this->start] = this->data[i];
		i++;
	}
	str[length] = 0;
	ctor(&new, str);
	free(str);
	return (new);
}

// void    getfunc_cp(t_string this)
// {
//     this->strcpy = strcpy;
//     this->strncpy = strncpy;
// }