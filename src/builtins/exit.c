/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 05:04:13 by danimart          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:52 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	get_exit_code(const char *str)
{
	unsigned long		i;
	unsigned long long	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i++] - '0');
		else
			return (255);
	}
	if (res > __LONG_MAX__)
		return (255);
	if (str[i] == '-')
		return (-res);
	return (res);
}

int	bin_exit(char **input, int *exit_code)
{
	if (input[0] == NULL)
	{
		*exit_code = 0;
		return (1);
	}
	else if (input[1] != NULL)
	{
		write(1, "exit: Too many arguments.\n", 27);
		return (0);
	}
	*exit_code = get_exit_code(input[0]);
	return (1);
}
