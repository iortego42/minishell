/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2024/03/06 17:18:23 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes builtins with the specified input.
 * 
 * @param input terminal input, this may change.
 * @param exit_code a pointer to an integer that will
 * be assigned to the exit code of the executed builtin.
 * 
 * @return 1 if minishell should exit (exit builtin),
 * 0 otherwise.
 */
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

void	sig_cancel(int signal)
{
	(void) signal;
	ioctl(0, TIOCSTI, "\n");
}

char	*get_prompt(char *suff)
{
	return (ft_strjoin(getenv("USER"), suff));
}

int	main(void)
{
	int		exit_code;
	int		stop;
	char	*cmd;
	char	*prompt;

	exit_code = 0;
	stop = 0;
	signal(SIGINT, sig_cancel);
	while (!stop)
	{
		prompt = get_prompt("$ ");
		cmd = readline(prompt);
		add_history(cmd);
		stop = process_builtins(cmd, &exit_code);
		free(prompt);
		free(cmd);
	}
	return (exit_code);
}
