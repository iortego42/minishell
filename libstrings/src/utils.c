#include "libstrings.h"

size_t	len(t_string this)
{
	size_t	length;

	if (this == NULL || this->data == NULL)
		return (0);
	if (this->end > this->start)
	{
		length = this->end - this->start;
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

void	p_findword(t_string this, char *delimitator)
{
	size_t	new_start;
	size_t	del_len;

	del_len = p_len(delimitator);
	while (p_str_ncmp(this, delimitator, del_len) == -1)
		this->start += del_len;
	new_start = this->start;
	while (this->start < this->end && p_str_ncmp(this, delimitator,
			del_len) >= 0)
		this->start++;
	this->end = this->start;
	this->start = new_start;
}

void	findword(t_string this, t_string delimitator)
{
	size_t	del_len;
	size_t	new_start;

	del_len = len(delimitator);
	while (str_ncmp(this, delimitator, del_len) == -1)
		this->start += del_len;
	new_start = this->start;
	while (this->start < this->end && str_ncmp(this, delimitator, del_len) >= 0)
		this->start++;
	this->end = this->start;
	this->start = new_start;
}
