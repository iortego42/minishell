/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:07:14 by iortego-          #+#    #+#             */
/*   Updated: 2022/06/30 11:49:27 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const	*s1, char const	*set)
{	
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 != 0 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1) - 1;
	while (s1[len] != 0 && ft_strchr(set, s1[len]))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
