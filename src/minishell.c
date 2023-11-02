/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 10:05:13 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_builtins(char *input, int *exit_code)
{
	if (ft_strstartswith(input, "exit"))
		return (bin_exit(input + 5, exit_code));
	else if (ft_strstartswith(input, "echo "))
		*exit_code = bin_echo(0, input + 5);
	else if (ft_strstartswith(input, "pwd"))
		bin_pwd();
	else if (ft_strstartswith(input, "cd "))
		chdir(input + 3);
	else if (ft_strstartswith(input, "env"))
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
	int		exit_code;
	int		stop;
	char	*cmd;

	exit_code = 0;
	stop = 0;
	signal(SIGINT, sig_cancel);
	while (!stop)
	{
		cmd = readline("minishell > ");
		add_history(cmd);
		stop = process_builtins(cmd, &exit_code);
		free(cmd);
	}
	return (exit_code);
}
