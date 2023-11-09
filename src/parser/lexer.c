/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:48:58 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/09 13:44:13 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_symbols(const char	*sequence)
{
	int		index;
	int		q_end;
	int		symbol_c;
	t_types	symbol;

	symbol_c = 0;
	index = 0;
	while (sequence[index] != 0)
	{
		symbol = is_symbol(&sequence[index]);
		if (symbol != -1)
			symbol_c++;
		if (symbol == SIMPLE_QUOTES || symbol == DOUBLE_QUOTES)
		{
			q_end = is_quote_terminated(&sequence[index]);
			if (q_end == FALSE)
				return (-1);
			index += q_end;
		}
		index++;
	}
	return (index);
}

t_symbol	*lexer(const char	*sequence)
{
	t_symbol	*sym_l;
	int			index;
	int			symbol_c;
	t_types		symbol;

	symbol_c = count_symbols(sequence);
	if (symbol_c == -1)
		return (NULL);
	index = 0;
	sym_l = malloc(sizeof(t_symbol) * (symbol_c + 1));
	if (sym_l == NULL)
		return (NULL);
	if (get_symbols(sequence, &sym_l))
		return (sym_l);
	free(sym_l);
	return (NULL);
}

int	get_symbols(const char	*sequence, t_symbol	**s)
{
	int		index;
	int		symbol_i;
	t_types	symbol;

	index = 0;
	symbol_i = 0;
	while (sequence[index] != 0)
	{
		symbol = is_symbol(&sequence[index]);
		if (symbol != -1)
		{
			s[0][symbol_i] = (t_symbol){.type = symbol, .pos = index};
			symbol_i++;
		}
		if (symbol == SIMPLE_QUOTES && symbol == DOUBLE_QUOTES)
			index += is_quote_terminated(&sequence[index]);
		index++;
	}
	return (symbol_i);
}

t_types	is_symbol(const	char	*sequence)
{
	t_types	index;

	index = 0;
	while (index < T_SIZE)
	{
		if (ft_strnstr(sequence, g_symbol[index],
				ft_strlen(g_symbol[index])) != NULL)
			return (index);
		index++;
	}
	return (-1);
}

int	is_quote_terminated(const char	*sequence)
{
	int		index;
	t_types	symbol;
	char	quote;

	symbol = is_symbol(sequence);
	quote = g_symbol[symbol][0];
	index = 1;
	while (sequence[index] != '\0')
	{
		if (sequence[index] == quote)
			return (index);
		index++;
	}
	return (FALSE);
}
