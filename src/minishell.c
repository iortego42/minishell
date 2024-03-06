/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2024/03/06 21:46:41 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*init_shell(void)
{
	t_sh	*shell;

	shell = malloc(sizeof(shell));
	if (shell == NULL)
		return (NULL);
	return (shell);
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
	t_sh	*shell;
	int		exit_code;
	int		stop;
	char	*cmd;
	char	*prompt;

	exit_code = 0;
	stop = 0;
	shell = init_shell();
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
