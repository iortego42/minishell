#include "libstrings.h"

void	clearlist(t_string *string)
{
	size_t	i;

	i = 0;
	while (string[i])
		dtor(&string[i]);
	free(string);
	string = NULL;
}
