#include "libstrings.h"

// static void getfunc(t_string string)
// {
//     if (!string)
//         return ((void)"");
//     getfunc_io(string);
//     getfunc_cp(string);
// }

void	dtor(t_string *string)
{
	if (!string || !(*string))
		return ((void)"");
	free((*string)->data);
	(*string)->data = NULL;
	free(*string);
	*string = NULL;
}

void	ctor(t_string *string, char *data)
{
	if (!string)
		return ((void)"");
	*string = malloc(sizeof(struct s_str));
	if (*string)
	{
		(*string)->start = 0;
		(*string)->end = 0;
		(*string)->data_len = 0;
		if (data)
		{
			while (data[(*string)->end])
				(*string)->end++;
			(*string)->data = malloc(sizeof(char) * ((*string)->end + 1));
			while ((*string)->data && data[(*string)->data_len])
			{
				(*string)->data[(*string)->data_len] = data[(*string)->data_len];
				(*string)->data_len++;
			}
			(*string)->data[(*string)->data_len] = 0;
		}
	}
}
