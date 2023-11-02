/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:02:26 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 06:35:13 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_echo(int fd, char *input)
{
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	return (0);
}
