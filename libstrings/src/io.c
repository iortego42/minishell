#include "libstrings.h"

void	print(t_string string)
{
	size_t	i;
	
	if (string && string->data)
	{
		i = string->start;
		while (i < string->end)
		{
			write(1, &string->data[i], 1);
			i++;
		}
	}
}

void	printe(t_string string)
{
	size_t	i;

	if (string && string->data)
	{
		i = string->start;
		while (i < string->end)
		{
			write(2, &string->data[i], 1);
			i++;
		}
	}
}

void	printfd(t_string string, int fd)
{
	size_t	i;

	if (string && string->data)
	{
		i = string->start;
		while (i < string->end)
		{
			write(fd, &string->data[i], 1);
			i++;
		}
	}
}

void	printnl(t_string string)
{
	size_t	i;

	if (string && string->data)
	{
		i = string->start;
		while (i < string->end)
		{
			write(1, &string->data[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}

// void    getfunc_io(t_string string)
// {
//     string->print = print;
//     string->printe = printe;
//     string->printfd = printfd;
//     // string->f[PRINT] = (void *(*)(t_string))print;
//     // string->f[PRINTE] = (void *(*)(t_string))printe;
//     // string->f[PRINTFD] = (void *(*)(t_string))printfd;
// }