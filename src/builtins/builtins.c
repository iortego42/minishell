/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:41:21 by danimart          #+#    #+#             */
/*   Updated: 2024/03/06 20:42:45 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_builtins(char *input, int *exit_code)
{
	if (ft_strstartswith(input, "exit"))
		return (bin_exit(input + 5, exit_code));
	else if (ft_strstartswith(input, "echo "))
		*exit_code = bin_echo(0, input + 5);
	else if (ft_strequals(input, "pwd"))
		*exit_code = bin_pwd();
	else if (ft_strstartswith(input, "cd "))
		*exit_code = chdir(input + 3);
	else if (ft_strequals(input, "env"))
		*exit_code = bin_env();
	return (0);
}
