/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfusion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:16:30 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/17 16:16:46 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstfusion_(t_list *left, t_list *right, int (*cmp)(void *,
		void *))
{
	t_list	*next;
	int		val;

	while (right && left->next)
	{
		val = cmp(left->next->content, right->content);
		if (val == 0)
			right = right->next;
		else if (val < 0)
		{
			next = right->next;
			right->next = left->next;
			left->next = right;
			left = right;
			right = next;
		}
		else
			left = left->next;
	}
	left->next = right;
}

void		ft_lstfusion(t_list **left, t_list *right, int (*cmp)(void *,
			void *))
{
	t_list	*tmp;
	t_list	*next;

	if (!left || !right)
		return ;
	if (!*left)
	{
		*left = right;
		return ;
	}
	tmp = *left;
	if (cmp(right->content, tmp->content) < 0)
	{
		next = right->next;
		right->next = tmp;
		*left = right;
		right = next;
		tmp = *left;
	}
	while (right && cmp(right->content, tmp->content) == 0)
		right = right->next;
	ft_lstfusion_(*left, right, cmp);
}
