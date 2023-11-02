/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:47:37 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/02 10:05:27 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef enum s_boolean {FALSE, TRUE}	t_bool;

/**
 * @brief Gets the length of a string. If str is
 * NULL, 0 will be returned.
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
t_bool	ft_strstartswith(char *str, char *prefix);

/**
 * @brief Gets a substring of the supplied
 * string until ch is found, so for example
 * ft_substr("Hello 42", ' ') will return
 * "Hello". If ch isn't found on str, a copy
 * of str will be returned. Yes, that means
 * that using '\0' as the delimiting character
 * will result in a method that copies strings.
 * 
 * @param str The main string to get the 
 * substring from.
 * @param ch The delimiting character for
 * the new substring, this character will
 * not be included.
 * @return A substring of str until ch is found.
 */
char	*ft_substrchr(char *str, char ch);

#endif
