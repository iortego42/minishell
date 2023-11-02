/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:32:37 by iortego-          #+#    #+#             */
/*   Updated: 2023/06/07 18:17:04 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcharlen(const char *str, const char sentinel)
{
	char	*s;

	s = (char *)str;
	while (*s != sentinel && *s != 0)
		s++;
	if (*s == sentinel && sentinel != 0)
		s++;
	return ((int)(s - str));
}

static	int	ft_strncpy(char *dst, char *src, size_t size)
{
	size_t	count;

	count = 0;
	while (src[count] != 0 && size > count + 1)
	{
		dst[count] = src[count];
		count++;
	}
	if (size != 0)
		dst[count] = 0;
	return (count);
}

char	*str_realloc(char *str, size_t size)
{
	char	*astr;

	astr = (char *)malloc(size * sizeof(char));
	if (str && astr)
	{
		ft_strncpy(astr, str, size);
		free(str);
		str = NULL;
	}
	return (astr);
}
