/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:00:21 by danimart          #+#    #+#             */
/*   Updated: 2023/11/15 18:26:02 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substrchr(char *str, char ch)
{
	char	*substr;
	int		end;
	int		i;

	if (str == NULL)
		return (NULL);
	end = 0;
	i = 0;
	while (str[end] != ch && str[end] != '\0')
		end++;
	substr = malloc(end);
	if (substr == NULL)
		return (NULL);
	while (i < end)
	{
		substr[i] = str[i];
		i++;
	}
	return (substr);
}
