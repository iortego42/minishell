#include "libstrings.h"

void	print(t_string this)
{
	size_t	i;
	
	if (this && this->data)
	{
		i = this->start;
		while (i < this->end)
		{
			write(1, &this->data[i], 1);
			i++;
		}
	}
}

void	printe(t_string this)
{
	size_t	i;

	if (this && this->data)
	{
		i = this->start;
		while (i < this->end)
		{
			write(2, &this->data[i], 1);
			i++;
		}
	}
}

void	printfd(t_string this, int fd)
{
	size_t	i;

	if (this && this->data)
	{
		i = this->start;
		while (i < this->end)
		{
			write(fd, &this->data[i], 1);
			i++;
		}
	}
}

void	printnl(t_string this)
{
	size_t	i;

	if (this && this->data)
	{
		i = this->start;
		while (i < this->end)
		{
			write(1, &this->data[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}

// void    getfunc_io(t_string this)
// {
//     this->print = print;
//     this->printe = printe;
//     this->printfd = printfd;
//     // this->f[PRINT] = (void *(*)(t_string))print;
//     // this->f[PRINTE] = (void *(*)(t_string))printe;
//     // this->f[PRINTFD] = (void *(*)(t_string))printfd;
// }