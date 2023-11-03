/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:49:51 by iortego-          #+#    #+#             */
/*   Updated: 2022/07/06 10:49:53 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*fnode;
	t_list	*flst;

	flst = NULL;
	while (lst && f)
	{	
		fnode = ft_lstnew(f(lst->content));
		if (!fnode)
			ft_lstclear(&flst, del);
		ft_lstadd_back(&flst, fnode);
		lst = lst->next;
	}
	return (flst);
}
