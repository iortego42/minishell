/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:32:45 by iortego-          #+#    #+#             */
/*   Updated: 2023/07/23 12:07:53 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize, size_t size)
{
	void	*amem;

	amem = (void *)malloc(newsize);
	if (ptr && amem && size != 0)
	{
		ft_memcpy(amem, ptr, size);
		free(ptr);
		ptr = NULL;
	}
	return (amem);
}
