/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:09:52 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 05:22:48 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include <readline/readline.h>

// Builtins

/**
 * @brief The echo builtin command.
 * 
 * @param fd The fd to use.
 * @param input The input to use, the "-n" flag
 * is supported, which removes the "\\n" added by
 * echo at the end of the input.
 * @return Currently always 0.
 */
int	bin_echo(int fd, char *input);

/**
 * @brief The exit builtin command.
 * 
 * @param input The input to use, generally just an exit code.
 * @param exit_code An integer pointer that will be set
 * with the corresponding exit code, if any.
 * @return Always 1, as this is used to exit the minishell.
 */
int	bin_exit(char *input, int *exit_code);

#endif
