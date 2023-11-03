/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:48:45 by iortego-          #+#    #+#             */
/*   Updated: 2022/07/06 11:33:50 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	while ((*lst)->next != NULL)
	{
		ft_lstdelone(*lst, *del);
		*lst = (*lst)->next;
	}
	ft_lstdelone(*lst, *del);
	*lst = NULL;
}	
