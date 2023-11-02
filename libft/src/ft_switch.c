/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:26:54 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/14 20:30:21 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_switch_mem(long long *a, long long *b)
{
	long long	*aux;

	aux = a;
	a = b;
	b = aux;
}

void	ft_switch_values(long long *a, long long *b)
{
	long long	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

void	ft_switch_int_values(int *a, int *b)
{
	int	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}
