/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:22:10 by iortego-          #+#    #+#             */
/*   Updated: 2022/06/27 15:22:16 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s1) + 1;
	copy = ft_calloc(len, sizeof(char));
	if (copy)
		ft_strlcpy(copy, s1, len);
	return (copy);
}
