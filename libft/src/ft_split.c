/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:49:43 by iortego-          #+#    #+#             */
/*   Updated: 2023/08/13 18:55:33 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	ft_how_many_char(char const *s, char sentinel)
{
	int	count;

	count = 0;
	while (*s != sentinel && *(s++) != 0)
		count++;
	return (count);
}

static int	ft_how_many_word(char const *s, char sentinel)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*(s) != 0)
		if (*(s++) != sentinel && (*s == sentinel || *s == 0))
			count++;
	return (count);
}

static void	ft_matrix_free(void **matrix, int dimension)
{
	int	free_count;

	free_count = 0;
	while (dimension-- > 0)
	{	
		while (*(matrix + free_count) != NULL && dimension > 0)
			ft_matrix_free(*(matrix + free_count++), dimension);
		free_count = 0;
		while (matrix + free_count != NULL)
			free(matrix + free_count++);
	}
}

static void	ft_matrix_delete(void **matrix, int dimension)
{
	ft_matrix_free(matrix, dimension);
	matrix = NULL;
}*/

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		words;
	int		n;

	words = ft_how_many_word(s, c);
	n = 0;
	list = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!list)
		return (NULL);
	while (words > n)
	{
		while (*s == c)
			s++;
		list[n] = (char *)ft_calloc(ft_how_many_char(s, c) + 1, sizeof(char));
		if (list[n] == NULL)
		{
			ft_matrix_delete((void ***)&list, 2);
			return (NULL);
		}
		ft_strlcpy(list[n], s, ft_how_many_char(s, c) + 1);
		s = ft_strchr(s, c);
		n++;
	}
	return (list);
}
