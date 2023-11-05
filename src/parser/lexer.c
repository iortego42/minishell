/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:48:58 by iortego-          #+#    #+#             */
/*   Updated: 2023/11/05 12:13:53 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_symbol	*lexer(const char	*sequence)
{
	t_symbol	*sym_l;
	int			index;
	int			token_c;
	t_types		symbol;

	token_c = 0;
	index = 0;
	while (sequence[index] != 0)
	{
		symbol = is_symbol(&sequence[index]);
		if (symbol != -1)
			token_c++;
		index++;
	}
	sym_l = malloc(sizeof(t_symbol) * (token_c + 1));
	if (sym_l == NULL)
		return (NULL);
	if (get_symbols(sequence, &sym_l))
		return (sym_l);
	free(sym_l);
	return (NULL);
}

t_bool	get_symbols(const char	*sequence, t_symbol	**s)
{
	int		index;
	int		token_i;
	t_types	token;

	index = 0;
	token_i = 0;
	while (sequence[index] != 0)
	{
		token = is_symbol(&sequence[index]);
		if (token != -1)
			s[0][token_i] = (t_symbol){.type = token, .pos = index};
		index++;
	}
	return (TRUE);
}

t_types	is_symbol(const	char	*sequence)
{
	t_types	index;

	index = 0;
	while (index < T_SIZE)
	{
		if (ft_strnstr(sequence, g_token[index],
				ft_strlen(g_token[index])) != NULL)
			return (index);
		index++;
	}
	return (-1);
}
