/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortego- <iortego-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:17:12 by iortego-          #+#    #+#             */
/*   Updated: 2023/05/14 19:19:45 by iortego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft.h"

typedef t_list	t_stack;

t_stack	*new_stack_element(void	*content);
void	push(t_stack **stack, t_stack *element);
void	swap(t_stack **stack);
void	rotate(t_stack **stack);
void	rev_rot(t_stack **stack);
t_bool	pop(t_stack **stack, void (*del)(void *));
t_stack	*peek(t_stack *stack);
void	delete_stack(t_stack **stack, void (*del)(void *));
int		size(t_stack	*stack);

#endif
