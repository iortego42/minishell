/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:01:42 by iortego-          #+#    #+#             */
/*   Updated: 2024/03/06 21:49:17 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_sh *shell)
{
	extern char	**environ;

	shell->env = environ;
}

char	*get_env(t_sh *shell, char *name)
{
	int		i;
	char	*env;
	int		env_len;

	i = 0;
	init_env(shell);
	while (shell->env[i] != NULL)
	{
		env = ft_substrchr(shell->env[i], '=');
		env_len = ft_strlen(env);
		if (ft_strequals(env, name))
			return (ft_substr(shell->env[i], env_len + 1, ft_strlen(shell->env[i]) - env_len));
		i++;
	}
	return (NULL);
}

/*char	*get_var_value(char	*env_entry)
{
	int	i;

	i = 0;
	while (env_entry[i] != '=' && env_entry[i] != 0)
		i++;
	if (env_entry[i] != '=')
		return (NULL);
	env_entry += i;
	return (ft_strdup(env_entry));
}

char	*expander(char	*sequence, int len, char	**env)
{
	int		count;
	char	*var;

	count = 0;
	var = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(var, sequence, len);
	var[len] = 0;
	while (ft_strncmp(var, env[count], len) == FALSE && env[count] != NULL)
		count++;
	free(var);
	if (env[count] == NULL)
		return (NULL);
	var = get_var_value(env[count]);
	return (var);
}*/
