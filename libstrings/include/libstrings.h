#ifndef STRINGS_H
# define STRINGS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_str	*t_string;

//  stirng.c
void					dtor(t_string *string);
void					ctor(t_string *string, char *data);
//  io.c
void					print(t_string string);
void					printe(t_string string);
void					printfd(t_string string, int fd);
void					printnl(t_string string);
//  cp.c
t_string				str_cpy(t_string string);
t_string				str_ncpy(t_string string, size_t size);
//  cmp.c
long int				str_cmp(t_string one, t_string two);
long int				str_ncmp(t_string one, t_string two, size_t max);
long int				p_str_cmp(t_string one, char *two);
long int				p_str_ncmp(t_string one, char *two, size_t max);
long int				endswith(t_string string, t_string s_suffix,
							char *p_suffix);
//	join.c
t_string				str_joinfront(t_string string, t_string preffix);
t_string				p_str_joinfront(t_string string, char *preffix);
t_string				str_joinback(t_string string, t_string suffix);
t_string				p_str_joinback(t_string string, char *suffix);
//  split.c
t_string				*split(t_string string, t_string delimitator);
void					printlist(t_string *string, t_string separator);
t_string				*nsplit(t_string string, size_t splits, size_t *position);
//	p_split.c
t_string				*p_split(t_string string, char *delimitator);
void					p_printlist(t_string *string, char *separator);
char					**strlstocharls(t_string *list);
//	nsplit.c
t_string				*nsplit(t_string string, size_t splits, size_t *position);
t_string				lstostr(t_string *list);
//	sub.c
t_string    			substr_rm(t_string  string, t_string substr);
t_string    			p_substr_rm(t_string  string, char *substr);
long					substr(t_string string, t_string substr);
long    				p_substr(t_string string, char *substr);
//	rm.c
void					clearlist(t_string *string);
// utils.c
void					findword(t_string string, t_string delimitator);
void					p_findword(t_string string, char *delimitator);
size_t					len(t_string string);
size_t					p_len(char	*str);
// get_set.c
char    				get(t_string string, size_t index);
char    				set(t_string string, size_t index, char value);

struct					s_str
{
	size_t				start;
	size_t				end;
	char				*data;
	size_t				data_len;
};
#endif
