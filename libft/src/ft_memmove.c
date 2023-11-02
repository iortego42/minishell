/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:22:09 by iortego-          #+#    #+#             */
/*   Updated: 2022/06/29 13:25:08 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define CAST unsigned char

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	count;

	count = 0;
	if (src < dest)
		while (0 < len--)
			((CAST *)dest)[len] = ((const CAST *)src)[len];
	else if (src > dest)
		while (len > count++)
			((CAST *)dest)[count - 1] = ((const CAST *)src)[count - 1];
	return (dest);
}
