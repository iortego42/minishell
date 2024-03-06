/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachh <nachh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:47:37 by iortego-          #+#    #+#             */
/*   Updated: 2024/03/06 06:15:09 by nachh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define UC unsigned char

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

typedef enum s_boolean {FALSE, TRUE}	t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s1);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

/*--FUNCIONES ADICIONALES*/

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int a, int fd);
/*-----PARTE BONUS-----*/
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *newnode);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *newnode);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*--MIS FUNCIONES--*/
t_list		*ft_lstfirst(t_list *lst);
/**
 * @brief Checks if a string is equal to another.
 * This will return TRUE if both stings are
 * the same size and have the same content or are NULL.
 * Note that characters after a '\0' character are
 * completely ignored.
 * 
 * @param a the first string.
 * @param b the second string.
 * @return TRUE if both strings are considered equal, FALSE otherwise.
 */
t_bool		ft_strequals(char *a, char *b);

/**
 * @brief Checks if a string starts with a
 * specific prefix. If prefix is longer than
 * str or any of the parameters is NULL, FALSE
 * will be returned directly.
 * 
 * @param str the string to check.
 * @param prefix the prefix to check.
 * @return TRUE if str starts with the specified
 * prefix, false otherwise.
 */
t_bool		ft_strstartswith(char *str, char *prefix);

/**
 * @brief Gets a substring of the supplied
 * string until ch is found, so for example
 * ft_substr("Hello 42", ' ') will return
 * "Hello". If ch isn't found on str, a copy
 * of str will be returned. Yes, that means
 * that using '\0' as the delimiting character
 * will result in a method that copies strings.
 * 
 * @param str The main string to get the 
 * substring from.
 * @param ch The delimiting character for
 * the new substring, this character will
 * not be included.
 * @return A substring of str until ch is found.
 */
char		*ft_substrchr(char *str, char ch);

int			ft_isspace(char c);
void		ft_switch_int_values(int *a, int *b);
void		ft_switch_values(long long int *a, long long int *b);
void		ft_switch_mem(long long int *a, long long int *b);
int			ft_how_many_word(char const *s, char sentinel);
int			ft_how_many_char(char const *s, char sentinel);
void		ft_matrix_delete(void ***matrix, int dimension);
void		ft_matrix_free(void **matrix, int dimension);
void		*ft_realloc(void	*ptr, size_t newsize, size_t size);
t_bool		extension(const	char *str, const char *ext);
char		**ft_matrixcpy(char	**m);
#endif
