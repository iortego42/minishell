/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:02:26 by danimart          #+#    #+#             */
/*   Updated: 2024/03/07 18:18:33 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_echo(int fd, char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		write(fd, input[i], ft_strlen(input[i]));
		i++;
	}
	if (!ft_strequals(input[0], "-n"))
		write(fd, "\n", 1);
	return (0);
}
