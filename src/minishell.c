/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 06:11:18 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_builtins(char *input, int *exit_code)
{
	if (startswith(input, "exit"))
		return (bin_exit(input + 5, exit_code));
	else if (startswith(input, "echo "))
		*exit_code = bin_echo(0, input + 5);
	return (0);
}

int	main(void)
{
	int	exit_code;
	int	stop;

	exit_code = 0;
	stop = 0;
	while (!stop)
		stop = process_builtins(readline("minishell > "), &exit_code);
	return (exit_code);
}
