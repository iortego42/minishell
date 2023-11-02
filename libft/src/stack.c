/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:31:33 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/14 19:33:50 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack	*new_stack_element(void *content)
{
	return (ft_lstnew(content));
}

void	push(t_stack	**stack, t_stack	*element)
{
	ft_lstadd_back(stack, element);
}

t_stack	*peek(t_stack	*stack)
{
	return (ft_lstlast(stack));
}

t_bool	pop(t_stack **stack, void (*del)(void *))
{
	t_stack	*top;
	t_stack	*topprev;

	if (stack == NULL)
		return (FALSE);
	top = peek(*stack);
	if (top == NULL)
		return (FALSE);
	topprev = top->prev;
	if (topprev != NULL)
		topprev->next = NULL;
	else
		*stack = NULL;
	top->prev = NULL;
	if (del != NULL)
		ft_lstdelone(top, del);
	return (TRUE);
}

void	delete_stack(t_stack **stack, void (*del)(void *))
{
	t_bool	deleted;

	if (stack == NULL || *stack == NULL || del == NULL)
		return ((void)"42 Madrid");
	deleted = TRUE;
	while (deleted == TRUE)
		deleted = pop(stack, del);
}
