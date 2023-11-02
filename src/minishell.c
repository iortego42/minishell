/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 09:30:38 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_builtins(char *input, int *exit_code)
{
	if (startswith(input, "exit"))
		return (bin_exit(input + 5, exit_code));
	else if (startswith(input, "echo "))
		*exit_code = bin_echo(0, input + 5);
	else if (startswith(input, "pwd"))
		bin_pwd();
	else if (startswith(input, "cd "))
		chdir(input + 3);
	else if (startswith(input, "env"))
		bin_env();
	return (0);
}

void	sig_cancel(int signal)
{
	(void) signal;
	ioctl(0, TIOCSTI, "\n");
}

int	main(void)
{
	int	exit_code;
	int	stop;

	exit_code = 0;
	stop = 0;
	signal(SIGINT, sig_cancel);
	while (!stop)
		stop = process_builtins(readline("minishell > "), &exit_code);
	return (exit_code);
}
