/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:30:07 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/09 13:33:33 by iortego-         ###   ########.fr       */
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
	SPACE,
	DOLLAR,
	PIPE,
	T_SIZE
}	t_types;

const static char	*g_symbol[T_SIZE] = {
[SIMPLE_QUOTES] = "'",
[DOUBLE_QUOTES] = "\"",
[OUTPUT_RED] = ">",
[INPUT_RED] = "<",
[SPACE] = " ",
[DOLLAR] = "$",
[PIPE] = "|",
};
typedef struct s_symbol
{
	int		pos;
	t_types	type;
}	t_symbol;
typedef struct s_syntaxnode
{
	t_symbol	symbol;
	char		*sequence;
	t_s_node	*next;	
	t_s_node	*prev;
}	t_s_node;
t_symbol	*lexer(const char	*sequence);
int			count_symbols(const char	*sequence);
t_types		is_symbol(const char	*sequence);
int			get_symbols(const char	*sequence, t_symbol	**s);

t_s_node	*parser(const char	*sequence);





#endif