/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchrindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:09:46 by danimart          #+#    #+#             */
/*   Updated: 2024/03/06 21:32:47 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchrindex(const char *str, int start, char ch)
{
	if (str == NULL)
		return (-1);
	while (str[start] != '\0')
	{
		if (str[start] == ch)
			return (start);
		start++;
	}
	return (-1);
}
