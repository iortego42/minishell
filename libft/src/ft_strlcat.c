/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:22:10 by iortego-          #+#    #+#             */
/*   Updated: 2022/06/29 11:40:51 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	count;

	count = 0;
	dstlen = 0;
	while (dst[dstlen] != 0 && dstlen < dstsize)
		dstlen++;
	if (dstsize == dstlen)
		return (dstlen + ft_strlen(src));
	while (src[count] != 0 && dstlen + count + 1 < dstsize)
	{
		dst[count + dstlen] = src[count];
		count++;
	}
	dst[dstlen + count] = 0;
	return (dstlen + ft_strlen(src));
}
