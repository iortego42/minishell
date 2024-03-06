#include "libstrings.h"

// static int wordcount(t_string   string, char  *delimitator)
static int	wordcount(t_string string, t_string delimitator)
{
	int			words;
	size_t		init_start;
	t_string	next;

	words = 0;
	next = str_cpy(string);
	if (!next)
		return (0);
	init_start = string->start;
	while (next->start < next->end)
	{
		findword(next, delimitator);
		words++;
		next->start = next->end;
		next->end = string->end;
	}
	string->start = init_start;
	dtor(&next);
	return (words);
}

static void	rclearlist(t_string *string, size_t	size)
{
	while (size-- > 0)
		dtor(&string[size]);
	free(string);
	string = NULL;
}

t_string	*split(t_string string, t_string delimitator)
{
	size_t		w;
	size_t		list_size;
	t_string	str;
	t_string	*list;

	w = 0;
	list_size = wordcount(string, delimitator);
	list = malloc(sizeof(t_string) * (list_size + 1));
	if (!list)
		return (NULL);
	str = str_cpy(string);
	if (!str)
		return (NULL);
	while (w++ < list_size)
	{
		findword(str, delimitator);
		list[w - 1] = str_cpy(str);
		if (list[w - 1] == NULL)
			return (dtor(&str), rclearlist(list, --w), NULL);
		str->start = str->end;
		str->end = string->end;
	}
	list[w - 1] = NULL;
	dtor(&str);
	return (list);
}

void	printlist(t_string *string, t_string separator)
{
	size_t	i;

	if (!string)
		return ;
	i = 0;
	while (string[i] != NULL)
	{
		print(string[i]);
		i++;
		if (string[i] != NULL)
			print(separator);
	}
}