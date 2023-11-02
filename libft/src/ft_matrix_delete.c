/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:29:19 by iortego-          #+#    #+#             */
/*   Updated: 2023/08/13 17:37:36 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_delete(void ***matrix, int dimension)
{
	ft_matrix_free(*matrix, --dimension);
	*matrix = NULL;
}

void	ft_matrix_free(void **matrix, int dimension)
{
	int	index;

	index = 0;
	while (*matrix != NULL)
	{
		if (dimension > 1)
			ft_matrix_free((void **) *matrix, dimension--);
		while (matrix[index] != NULL)
		{
			free(matrix[index]);
			matrix[index] = NULL;
			index++;
		}
		matrix++;
	}
}
