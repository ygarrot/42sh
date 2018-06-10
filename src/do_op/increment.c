/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:35:20 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 18:11:17 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	set_op_variable(char *key, int value)
{
	char *todel[2];
	
	*todel = ft_itoa(value);
	todel[1] = ft_implode("=", key, *todel);
	ft_variable_builtin(todel[1]);
	ft_memdel((void**)&todel[1]);
	ft_memdel((void**)&todel[0]);
}

int		unaire(t_do_op **b)
{
	t_do_op *todel;
	t_do_op *a;

	a = *b;
	if (!ft_strcmp(a->content, "++") || !ft_strcmp(a->content, "--"))
		increment(a, !ft_strcmp(a->content, "++") ? 1 : -1);
	else if (!ft_strcmp(a->content, "-") || !ft_strcmp(a->content, "+"))
	{
		if (a->next->code != -1 && ft_strcmp(a->next->content, "-") 
	&& ft_strcmp(a->next->content, "+"))
		return (0);
		a->next->sign = (a->sign | 1) * (*a->content == '+' ? 1 : -1);
		return (unaire(&(*b)->next));
	}
	else
		return (0);
	todel = *b;
	*b = (*b)->next;
	free_op(todel);
	return (1);
}

void	increment(t_do_op *a, int i)
{
	t_do_op *r;
	char *s;

	r = ((!a->next || a->next->code >= 0)  ? a->prev : a->next);
	if (!r || (r == a->prev && (r->is_inc = i)))
		return ;
	ft_printf("ici\n");
	s = ft_variablepars(r->content);
	set_op_variable(r->content, ft_atoi(s) + i);
	ft_memdel((void**)&s);
}
