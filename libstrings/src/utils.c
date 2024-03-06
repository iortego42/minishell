#include "libstrings.h"

size_t	len(t_string string)
{
	size_t	length;

	if (string == NULL || string->data == NULL)
		return (0);
	if (string->end > string->start)
	{
		length = string->end - string->start;
		return (length);
	}
	else
		return (0);
}

size_t	p_len(char	*str)
{
	size_t	length;

	if (str == NULL)
		return (0);
	length = 0;
	while (str[length])
		length++;
	return (length);
}

void	p_findword(t_string string, char *delimitator)
{
	size_t	new_start;
	size_t	del_len;

	del_len = p_len(delimitator);
	while (p_str_ncmp(string, delimitator, del_len) == -1)
		string->start += del_len;
	new_start = string->start;
	while (string->start < string->end && p_str_ncmp(string, delimitator,
			del_len) >= 0)
		string->start++;
	string->end = string->start;
	string->start = new_start;
}

void	findword(t_string string, t_string delimitator)
{
	size_t	del_len;
	size_t	new_start;

	del_len = len(delimitator);
	while (str_ncmp(string, delimitator, del_len) == -1)
		string->start += del_len;
	new_start = string->start;
	while (string->start < string->end && str_ncmp(string, delimitator, del_len) >= 0)
		string->start++;
	string->end = string->start;
	string->start = new_start;
}
