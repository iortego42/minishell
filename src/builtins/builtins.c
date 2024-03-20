/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:41:21 by danimart          #+#    #+#             */
/*   Updated: 2024/03/20 04:57:10 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_input(char **input)
{
	int	i;

	i = 0;
	printf("Builtin input:\n");
	while (input[i] != NULL)
	{
		printf("%d = %s\n", i, input[i]);
		i++;
	}
}

int	process_builtins(char **input, int *exit_code)
{
	debug_input(input);
	if (ft_strequals(input[0], "exit"))
		return (bin_exit(input + 1, exit_code));
	else if (ft_strequals(input[0], "echo"))
		*exit_code = bin_echo(0, input + 1);
	else if (ft_strequals(input[0], "pwd"))
		*exit_code = bin_pwd(input + 1);
	else if (ft_strequals(input[0], "cd"))
		*exit_code = bin_cd(input + 1);
	else if (ft_strequals(input[0], "env"))
		*exit_code = bin_env();
	return (0);
}
