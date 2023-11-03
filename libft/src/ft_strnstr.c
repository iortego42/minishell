/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:22:10 by iortego-          #+#    #+#             */
/*   Updated: 2022/09/06 19:54:24 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*haystack, const char	*needle, size_t	len)
{
	size_t	nlen;
	size_t	count;

	if (*needle == 0)
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	while (*haystack != 0 && len-- >= nlen)
	{
		count = 0;
		while (haystack[count] != 0 && haystack[count] == needle[count])
			count++;
		if (needle[count] == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
