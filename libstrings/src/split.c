#include "libstrings.h"

// static int wordcount(t_string   this, char  *delimitator)
static int	wordcount(t_string this, t_string delimitator)
{
	int			words;
	size_t		init_start;
	t_string	next;

	words = 0;
	next = str_cpy(this);
	if (!next)
		return (0);
	init_start = this->start;
	while (next->start < next->end)
	{
		findword(next, delimitator);
		words++;
		next->start = next->end;
		next->end = this->end;
	}
	this->start = init_start;
	dtor(&next);
	return (words);
}

static void	rclearlist(t_string *this, size_t	size)
{
	while (size-- > 0)
		dtor(&this[size]);
	free(this);
	this = NULL;
}

t_string	*split(t_string this, t_string delimitator)
{
	size_t		w;
	size_t		list_size;
	t_string	str;
	t_string	*list;

	w = 0;
	list_size = wordcount(this, delimitator);
	list = malloc(sizeof(t_string) * (list_size + 1));
	if (!list)
		return (NULL);
	str = str_cpy(this);
	if (!str)
		return (NULL);
	while (w++ < list_size)
	{
		findword(str, delimitator);
		list[w - 1] = str_cpy(str);
		if (list[w - 1] == NULL)
			return (dtor(&str), rclearlist(list, --w), NULL);
		str->start = str->end;
		str->end = this->end;
	}
	list[w - 1] = NULL;
	dtor(&str);
	return (list);
}

void	printlist(t_string *this, t_string separator)
{
	size_t	i;

	i = 0;
	while (this[i] != NULL)
	{
		print(this[i]);
		i++;
		if (this[i] != NULL)
			print(separator);
	}
}