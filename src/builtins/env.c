/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:24:31 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 09:32:58 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	bin_env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
	{
		write(0, environ[i], ft_strlen(environ[i]));
		write(0, "\n", 1);
		i++;
	}
	return (0);
}
