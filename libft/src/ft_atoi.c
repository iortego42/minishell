/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:22:08 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/27 15:54:26 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	ft_isspace(char c)
{
	return ((unsigned)c - 9 < 5 || c == 32);
}*/

int	ft_atoi(const char *c)
{
	long int	ret;
	int			sing;

	ret = 0;
	sing = 1;
	while (ft_isspace(*c))
		c++;
	if (*c == '-')
		sing = -1;
	if (*c == '+' || *c == '-')
		c++;
	while (ft_isdigit(*c))
	{
		ret = (10 * ret) + *(c++) - '0';
		if (sing * ret > INT_MAX || sing * ret < INT_MIN)
			return (0);
	}
	return (ret * sing);
}
