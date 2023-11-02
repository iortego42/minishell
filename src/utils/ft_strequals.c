/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:06:20 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 10:18:49 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_strequals(char *a, char *b)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (a == NULL || b == NULL)
		return (a == NULL && b == NULL);
	len = ft_strlen(a);
	if (len != ft_strlen(b))
		return (FALSE);
	while (i < len)
	{
		if (a[i] != b[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
