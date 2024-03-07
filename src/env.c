/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:01:54 by danimart          #+#    #+#             */
/*   Updated: 2024/03/07 18:06:30 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_sh *shell, char *name)
{
	int			i;
	char		*env;
	int			env_len;
	extern char	**environ;

	i = 0;
	shell->env = environ;
	while (environ[i] != NULL)
	{
		env = ft_substrchr(environ[i], '=', 0);
		env_len = ft_strlen(env);
		if (ft_strequals(env, name))
		{
			free(env);
			return (ft_substrchr(environ[i], '\0', env_len + 1));
		}
		i++;
	}
	free(env);
	return (NULL);
}

char	*append_char(char *str, char ch)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = ch;
	res[i + 1] = '\0';
	free(str);
	return (res);
}

char	*add_envs(t_sh *shell, char *cmd)
{
	int		i;
	char	*expanded;
	char	*env;

	i = 0;
	printf("Adding envs to %s\n", cmd);
	expanded = malloc(sizeof(char));
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')
		{
			env = get_env(shell, ft_substrchr(cmd, ' ', i + 1));
			expanded = ft_strjoin(expanded, env);
			i += ft_strlen(ft_substrchr(cmd, ' ', i));
		}
		else
		{
			expanded = append_char(expanded, cmd[i]);
			i++;
		}
	}
	free(cmd);
	return (expanded);
}
