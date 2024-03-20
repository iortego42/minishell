/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:01:24 by danimart          #+#    #+#             */
/*   Updated: 2024/03/20 02:27:33 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(char **input)
{
	char	*pwd;

	if (input[0] != NULL)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	pwd = getwd(NULL);
	if (pwd == NULL)
		return (2);
	write(0, pwd, ft_strlen(pwd));
	write(0, "\n", 1);
	free(pwd);
	return (0);
}
