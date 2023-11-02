/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:02:26 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 06:41:59 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_echo(int fd, char *input)
{
	if (startswith(input, "-n"))
		write(fd, input + 3, ft_strlen(input + 3));
	else
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
	}
	return (0);
}
