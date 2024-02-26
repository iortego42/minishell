#include "libstrings.h"

void	clearlist(t_string *this)
{
	size_t	i;

	i = 0;
	while (this[i])
		dtor(&this[i]);
	free(this);
	this = NULL;
}
