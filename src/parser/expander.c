/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:01:42 by iortego-          #+#    #+#             */
/*   Updated: 2024/03/07 17:13:41 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_expanded_size(char *input)
{
	int		i;
	int		size;
	t_bool	quote;

	i = 0;
	size = 1;
	quote = FALSE;
	while (input[i] != '\0')
	{
		if (input[i] == '\"')
			quote = !quote;
		else if (!quote && input[i] == ' ')
			size++;
		i++;
	}
	return (size);
}

// echo Hi ",  world"

char	*get_next_arg(t_sh *shell, char *input, int *i)
{
	int		start;
	t_bool	quote;
	char	limit;

	quote = input[0] == '\"';
	limit = ' ';
	if (quote)
	{
		*i += 1;
		limit = '\"';
	}
	start = *i;
	while (input[*i] != '\0')
	{
		if (input[*i] == limit)
			break ;
		*i += 1;
	}
	return (add_envs(shell, ft_substr(input, start, *i - start)));
}

char	**expand(t_sh *shell, char *input)
{
	char	**cmds;
	int		cmds_size;
	int		cmds_i;
	int		in_i;

	cmds_size = (get_expanded_size(input) + 1);
	cmds = malloc(cmds_size * sizeof(char));
	cmds_i = 0;
	in_i = 0;
	while (cmds_i < cmds_size)
	{
		cmds[cmds_i] = get_next_arg(shell, input, &in_i);
		cmds_i++;
	}
	cmds[cmds_i] = NULL;
	return (cmds);
}
