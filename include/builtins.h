/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:00:31 by danimart          #+#    #+#             */
/*   Updated: 2024/03/07 17:46:21 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/**
 * @brief Executes builtins with the specified input.
 * 
 * @param input terminal input, this may change.
 * @param exit_code a pointer to an integer that will
 * be assigned to the exit code of the executed builtin.
 * 
 * @return 1 if minishell should exit (exit builtin),
 * 0 otherwise.
 */
int	process_builtins(char **input, int *exit_code);

/**
 * @brief The echo builtin command. Supports the "-n"
 * flag.
 * 
 * @param fd The fd to use.
 * @param input The command input to use.
 * @return Currently always 0.
 */
int	bin_echo(int fd, char **input);

/**
 * @brief The exit builtin command.
 * 
 * @param input The input to use, generally just an exit code.
 * @param exit_code An integer pointer that will be set
 * with the corresponding exit code, if any.
 * @return 1, on success as this is used to exit the minishell,
 * 0 if too many arguments were provided.
 */
int	bin_exit(char **input, int *exit_code);

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
