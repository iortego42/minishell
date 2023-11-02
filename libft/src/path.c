/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:04:57 by iortego-          #+#    #+#             */
/*   Updated: 2023/09/12 18:06:08by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	extension(const char *str, const char *ext)
{
	int		strlenn;
	int		extlen;
	char	*path;

	extlen = ft_strlen(ext);
	strlenn = ft_strlen(str);
	path = ft_strnstr(str + strlenn - extlen, ext, extlen);
	if (path == NULL || !ft_strncmp(path, str, strlenn))
		return (FALSE);
	return (TRUE);
}
