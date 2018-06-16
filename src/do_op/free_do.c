/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 11:05:49 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 17:25:16 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	free_op(t_do_op **tmp)
{
	if (!*tmp)
		return ;
	(*tmp)->next ? (*tmp)->next->prev = (*tmp)->prev : 0;
	(*tmp)->prev ? (*tmp)->prev->next = (*tmp)->next : 0;
	ft_memdel((void**)&(*tmp)->content);
	ft_memdel((void**)&(*tmp));
}

t_do_op	*del_ternary(t_do_op **c)
{
	t_do_op *tmp;

	if (!c && error_do_op("error do_op : del_ternary\n"))
		return (NULL);
	while (*c && (*c)->code != -2)
	{
		tmp = *c;
		*c = (*c)->next;
		free_op(&tmp);
	}
	if (!*c)
		return (NULL);
	tmp = *c;
	*c = (*c)->next;
	free_op(&tmp);
	return (*c);
}

int	del_after_exec(t_do_op **list)
{
	int *err;
	t_do_op *tmp[2];
	t_do_op *tern;

	tmp[1] = NULL;
	tern = *list;
	if (!(err = do_op((*list)->prev, *list, (*list)->next)))
		return (-1);
	(*list) = (*list)->prev;
	(*list)->value = *err; 
	(*list)->is_set = 1;
	if (*tern->content == '?')
		tmp[1] = del_ternary(&tern->next->next);
	tern = (*list)->next;
	*tmp = tern->next;
	if (tern && *tmp && (*tmp)->next)
		(*list)->next = tmp[1] ? tmp[1] : (*list)->next->next->next;
	free_op(&(*tmp));
	free_op(&tern);
	return (0);
}
