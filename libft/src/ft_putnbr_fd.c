/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:59:30 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/14 19:23:58 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int a, int fd)
{
	long int	n;
	int			count;

	count = 0;
	n = a;
	if (n < 0)
	{
		write(fd, "-", 1);
		count++;
	n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	count += ft_putchar_fd(n % 10 + '0', fd);
	return (count);
}
