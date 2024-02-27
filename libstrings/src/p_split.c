#include "libstrings.h"

// static int wordcount(t_string   this, char  *delimitator)
static int	wordcount(t_string this, char *delimitator)
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
		p_findword(next, delimitator);
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

t_string	*p_split(t_string this, char *delimitator)
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
		p_findword(str, delimitator);
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

void	p_printlist(t_string *this, char *separator)
{
	size_t	i;
	size_t	sep_len;

	if (!this)
		return ;
	i = 0;
	sep_len = p_len(separator);
	while (this[i] != NULL)
	{
		print(this[i]);
		i++;
		if (separator && this[i] != NULL)
			write(1, separator, sep_len);
	}
}

char	**strlstocharls(t_string *list)
{
	size_t	list_size;
	char	**strlist;

	if (!list)
		return ;
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