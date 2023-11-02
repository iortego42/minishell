/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:48:22 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/14 19:21:07 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newnode)
{
	t_list	*last;

	if (lst == NULL || newnode == NULL)
		return ;
	if (*lst == NULL)
		return (*lst = newnode, (void)"42madrid");
	last = ft_lstlast(*lst);
	last->next = newnode;
	newnode->prev = last;
	newnode->next = NULL;
}
