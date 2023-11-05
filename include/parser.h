/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:30:07 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/05 12:03:03 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "libft.h"

typedef enum s_type {
	SIMPLE_QUOTES,
	DOUBLE_QUOTES,
	OUTPUT_RED,
	INPUT_RED,
	PIPE,
	T_SIZE
}	t_types;

const static char	*g_token[T_SIZE] = {
[SIMPLE_QUOTES] = "'",
[DOUBLE_QUOTES] = "\"",
[OUTPUT_RED] = ">",
[INPUT_RED] = "<",
[PIPE] = "|",
};
typedef struct s_symbol
{
	int		pos;
	t_types	type;
}	t_symbol;
t_symbol	*lexer(const char	*sequence);
t_types		is_symbol(const char	*sequence);
t_bool		get_symbols(const char	*sequence, t_symbol	**s);




#endif