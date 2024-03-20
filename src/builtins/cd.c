/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:30:09 by danimart          #+#    #+#             */
/*   Updated: 2024/03/20 04:02:28 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_cd(char **input)
{
	if (input[1] == NULL)
		return (chdir(input[0]));
	printf("cd: too many arguments.");
	return (1);
}