/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2024/03/07 17:57:30 by danimart         ###   ########.fr       */
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

t_bool	process_input(t_sh	*shell, char *prompt, int *exit_code)
{
	char	*input;
	t_bool	res;

	input = readline(prompt);
	add_history(input);
	res = process_builtins(expand(shell, input), exit_code) == 1;
	free(prompt);
	free(input);
	return (res);
}

int	main(void)
{
	t_sh	*shell;
	int		exit_code;

	exit_code = 0;
	shell = init_shell();
	signal(SIGINT, sig_cancel);
	while (!process_input(shell, get_prompt("$ "), &exit_code))
		;
	return (exit_code);
}
