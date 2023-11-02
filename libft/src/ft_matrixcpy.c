/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:59:15 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/02 02:00:42 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_entries(char **m)
{
	int	entries;

	entries = 0;
	while (m[entries] != NULL)
		entries++;
	return (entries);
}

char	**ft_matrixcpy(char **m)
{
	char	**copy;
	int		index;

	index = get_entries(m) + 1;
	copy = (char **) malloc(sizeof(char *) * index);
	if (!copy)
		return (NULL);
	while (index-- > 0)
		copy[index] = NULL;
	index++;
	while (m[index] != NULL)
	{
		copy[index] = ft_strdup(m[index]);
		if (!copy[index])
			ft_matrix_delete((void ***)&copy, 2);
		index++;
	}
	return (copy);
}
