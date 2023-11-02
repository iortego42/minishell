/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:02:26 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 08:59:56 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_env(int fd, char *env)
{
	char	*name;
	char	*val;

	name = ft_substrchr(env, ' ');
	val = getenv(name);
	write(fd, val, ft_strlen(val));
	free(name);
	return (ft_strlen(name) + 1);
}

void	write_input(int fd, char *input, t_bool nl)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			i += write_env(fd, input + i + 1);
		write(fd, &input[i], 1);
		i++;
	}
	if (nl)
		write(fd, "\n", 1);
}

int	bin_echo(int fd, char *input)
{
	if (startswith(input, "-n"))
		write_input(fd, input + 3, FALSE);
	else
		write_input(fd, input, TRUE);
	return (0);
}
