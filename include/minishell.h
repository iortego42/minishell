/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:09:52 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 04:49:12 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>

int	bin_echo(int fd, char *input);

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef enum s_boolean {FALSE, TRUE}	t_bool;

/**
 * @brief Gets the length of a string.
 * 
 * @param str the string to use.
 * @return the length of the string.
 */
size_t	ft_strlen(const	char *str);

/**
 * @brief Checks if a string starts with a
 * specific prefix. If prefix is longer than
 * str or any of the parameters is NULL, FALSE
 * will be returned directly.
 * 
 * @param str the string to check.
 * @param prefix the prefix to check.
 * @return TRUE if str starts with the specified
 * prefix, false otherwise.
 */
t_bool	startswith(char *str, char *prefix);

#endif
