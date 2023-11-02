/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:12:22 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 05:03:28 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, int *exit_code)
{
	if (startswith(input, "echo "))
		*exit_code = bin_echo(0, input + 5);
}

int	main(void)
{
	int	exit_code;

	exit_code = 0;
	while (TRUE)
		process_input(readline("minishell > "), &exit_code);
	return (exit_code);
}
