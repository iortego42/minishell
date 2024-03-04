/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:02:26 by danimart          #+#    #+#             */
/*   Updated: 2024/03/04 18:51:57 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_input(int fd, char *input, t_bool nl)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
		i += write(fd, &input[i], 1);
	if (nl)
		write(fd, "\n", 1);
}

int	bin_echo(int fd, char *input)
{
	if (ft_strstartswith(input, "-n"))
		write_input(fd, input + 3, FALSE);
	else
		write_input(fd, input, TRUE);
	return (0);
}
