/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:22:10 by iortego-          #+#    #+#             */
/*   Updated: 2022/06/29 11:41:11 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	while (src[count] != 0 && dstsize > 1 + count && ++count)
		dst[count - 1] = src[count - 1];
	if (dstsize != 0)
		dst[count] = 0;
	return (ft_strlen(src));
}
