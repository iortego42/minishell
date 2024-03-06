#include "libstrings.h"

// static int wordcount(t_string   string, char  *delimitator)
static int	wordcount(t_string string, char *delimitator)
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
		p_findword(next, delimitator);
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

t_string	*p_split(t_string string, char *delimitator)
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
		p_findword(str, delimitator);
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

void	p_printlist(t_string *string, char *separator)
{
	size_t	i;
	size_t	sep_len;

	if (!string)
		return ;
	i = 0;
	sep_len = p_len(separator);
	while (string[i] != NULL)
	{
		print(string[i]);
		i++;
		if (separator && string[i] != NULL)
			write(1, separator, sep_len);
	}
}

char	**strlstocharls(t_string *list)
{
	size_t	list_size;
	char	**strlist;

	if (!list)
		return (NULL);
	list_size = 0;
	while (list[list_size] != NULL)
		list_size++;
	strlist = malloc(sizeof(char *) * (list_size + 1));
	if (!strlist)
		return (NULL);
	list_size = 0;
	while (list[list_size] != NULL)
	{
		strlist[list_size] = list[list_size]->data;
		list_size++;
	}
	strlist[list_size] = NULL;
	return (strlist);
}