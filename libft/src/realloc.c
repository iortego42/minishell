/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:32:45 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/02 02:03:46 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
