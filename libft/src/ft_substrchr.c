/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:00:21 by danimart          #+#    #+#             */
/*   Updated: 2024/03/07 15:19:19 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substrchr(char *str, char ch, int start)
{
	char	*substr;
	int		end;

	if (str == NULL)
		return (NULL);
	end = 0;
	while (str[end] != ch && str[end] != '\0')
		end++;
	if (start > end)
		return (NULL);
	substr = malloc(end);
	if (substr == NULL)
		return (NULL);
	while (start < end)
	{
		substr[start] = str[start];
		start++;
	}
	return (substr);
}
