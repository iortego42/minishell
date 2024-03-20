/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:00:21 by danimart          #+#    #+#             */
/*   Updated: 2024/03/20 05:16:12 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substrchr(char *str, char ch, int start)
{
	char	*substr;
	int		end;
	int		substr_i;

	if (str == NULL)
		return (NULL);
	end = 0;
	while (str[end] != ch && str[end] != '\0')
		end++;
	if (start > end)
		return (NULL);
	substr = malloc(end * sizeof(char));
	if (substr == NULL)
		return (NULL);
	substr_i = 0;
	while (start < end)
	{
		substr[substr_i] = str[start];
		start++;
		substr_i++;
	}
	return (substr);
}
