/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:10:25 by iortego-          #+#    #+#             */
/*   Updated: 2022/07/04 19:05:48 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_itoa(int n)
{
	char			*number;
	unsigned int	sign;
	int				digits;

	digits = 0;
	sign = n;
	if (n <= 0 && ++digits)
		sign = -n;
	while (sign > 0 && ++digits)
		sign /= 10;
	number = (char *)ft_calloc(digits + 1, sizeof(char));
	if (number == NULL)
		return (NULL);
	sign = n;
	if (n < 0)
		*(number) = '-';
	if (n < 0)
		sign = -n;
	while (digits-- > 0 && number[digits] != '-')
	{
		number[digits] = '0' + sign % 10;
		sign /= 10;
	}
	return (number);
}
