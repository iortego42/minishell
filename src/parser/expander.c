/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:01:42 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/17 18:44:35 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


char	*get_var_value(char	*env_entry)
{
	char	*value;

	while (*env_entry != '=' && *env_entry != 0)
		env_entry++;
	if (env_entry != '=')
		return (NULL);
	env_entry++;
	value = ft_strdup(env_entry);
	return (value);
}

char	*expander(char	*sequence, int len, char	**env)
{
	int		count;
	char	*var;

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
}
