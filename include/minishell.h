/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:09:52 by danimart          #+#    #+#             */
/*   Updated: 2023/11/05 12:02:28 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include "libft.h"
# include <readline/readline.h>

// Builtins

/**
 * @brief The echo builtin command. Supports the "-n"
 * flag and env variables such as $PATH.
 * 
 * @param fd The fd to use.
 * @param input The command input to use.
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

/**
 * @brief The pwd builtin command. This command doesn't
 * accept any type of arguments nor flags.
 * 
 * @return 1 on failure, 0 on success.
 */
int	bin_pwd(void);

/**
 * @brief The env builtin command. This command doesn't
 * accept any type of arguments nor flags.
 * 
 * @return Currently always 0.
 */
int	bin_env(void);

#endif
