/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:01:24 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 08:07:49 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(void)
{
	char	*pwd;

	pwd = getwd(NULL);
	if (pwd == NULL)
		return (1);
	write(0, pwd, ft_strlen(pwd));
	write(0, "\n", 1);
	free(pwd);
	return (0);
}
