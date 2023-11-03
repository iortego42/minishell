/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:32:07 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/15 14:19:39 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *c)
{
	long long	ret;
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
		ret = (10 * ret) + *(c++) - '0';
	return (ret * sing);
}
