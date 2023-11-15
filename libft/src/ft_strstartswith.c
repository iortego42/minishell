/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartswith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:08:28 by danimart          #+#    #+#             */
/*   Updated: 2023/11/15 18:25:10 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_strstartswith(char *str, char *prefix)
{
	int	str_len;
	int	prefix_len;
	int	i;

	if (str == NULL || prefix == NULL)
		return (FALSE);
	str_len = ft_strlen(str);
	prefix_len = ft_strlen(prefix);
	if (str_len < prefix_len)
		return (FALSE);
	i = 0;
	while (i < prefix_len)
	{
		if (str[i] != prefix[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
