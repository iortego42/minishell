/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:48:58 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/17 17:23:52 by iortego-         ###   ########.fr       */
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
				return (NONE);
			index += q_end;
		}
		index++;
	}
	return (index);
}

t_symbol	*lexer(const char	*sequence)
{
	t_symbol	*sym_l;
	int			symbol_c;

	symbol_c = count_symbols(sequence);
	if (symbol_c == NONE)
		return (NULL);
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
		if (symbol != NONE)
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
	t_types	s_index;

	s_index = 0;
	while (s_index < T_SIZE)
	{
		if (ft_strnstr(sequence, g_symbol[s_index],
				ft_strlen(g_symbol[s_index])) != NULL)
			return (s_index);
		s_index++;
	}
	return (NONE);
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
