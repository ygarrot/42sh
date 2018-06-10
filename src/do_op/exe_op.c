/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 15:43:55 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 18:22:36 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	free_op(t_do_op *tmp)
{
	tmp->next ? tmp->next->prev = tmp->prev : 0;
	tmp->prev ? tmp->prev->next = tmp->next : 0;
	ft_memdel((void**)&tmp->content);
	ft_memdel((void**)&tmp);
}

void	pre_op(t_do_op **list)
{
	t_do_op *tmp;
	
	if (*(*list)->content == '(')
	{
		(*list)->value = ft_atoi(parse_op((*list)->content));
		(*list)->is_set = 1;
		return ;
	}
	if (unaire(list))
		return ;
	tmp = (*list)->next->next;
	(*list)->prev->value = do_op((*list)->prev, *list, (*list)->next);
	(*list) = (*list)->prev;
	free_op((*list)->next->next);
	free_op((*list)->next);
	(*list)->is_set = 1;
	(*list)->next = tmp;
}

void	if_function(t_do_op **beg, int status)
{
	t_do_op *list = *beg;
	if ((status == 0 && (*list->content == '('
					|| get_sep(list->content, CREMENT) >= 0))||
			(status == 1 && (!ft_strcmp(list->content, "--") || !ft_strcmp(list->content, "++"))) ||
			(status == 2 && (!ft_strcmp(list->content, "-") || !ft_strcmp(list->content, "+"))) ||
			(status == 3 && ft_isin(*list->content, "~!")) ||
			(status == 4 && !ft_strcmp(list->content, "**")) ||
			(status == 5 && ft_isin(*list->content, "*/%")) ||
			(status == 6 && ft_isin(*list->content, "-+")) ||
			(status == 7 && (get_sep(list->content, SHIFT) >= 0)) ||
			(status == 8 && (get_sep(list->content, HCOMP) >= 0)) ||
			(status == 9 && (get_sep(list->content, LCOMP) >= 0)) ||
			(status == 10 && !ft_strcmp(list->content, "&")) ||
			(status == 11 && !ft_strcmp(list->content, "^")) ||
			(status == 12 && !ft_strcmp(list->content, "|")) ||
			(status == 13  && !ft_strcmp(list->content, "&&")) ||
			(status == 14 && !ft_strcmp(list->content, "||")) ||
			(status == 15 && !ft_strcmp(list->content, "?")))
		pre_op(beg);
}

int	the_order(t_do_op *begin)
{
	int i;
	int	ret;
	t_do_op *list;

	i = -1;
	while (begin && begin->next && ++i < 17)
	{
		list = begin;
		while (list)
		{
			if_function(&list, i);
			list && !list->prev ? begin = list : 0;
			list ? list = list->next : 0;
		}
	}
	if (begin)
	{
		!begin->is_set ? begin->value = get_value(begin) : 0;
		begin->is_set = 1;
	}
	ret = begin ? begin->value : 0;
	free_do_op(begin);
	return (ret);
}

int	set_assign(t_do_op *list)
{
//	char *tmp;

	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if (get_sep(list->content, all_op(1)) >= 0)
		{
			list->prev->value = the_order(list->next);
			list->next ? free_op(list->next) : 0;
			list = list->prev;
			set_op_variable(list->content, list->value);
			free_op(list->next);
			list->is_set = 1;
		}
		list->prev ? list = list->prev : 0;
	}
	return (the_order(list));
}

char		*exec_op(char **tb)
{
	t_do_op		*list;
	t_do_op		*begin;
	int			i;

	i = -1;
	list = (t_do_op*)ft_memalloc(sizeof(t_do_op));
	begin = list;
	while (tb[++i])
	{
		tb[i + 1] ? list->next = (t_do_op*)ft_memalloc(sizeof(t_do_op)) : 0;
		list->next ? list->next->prev = list : 0;
		list->content = tb[i];
		list = list->next;
	}
	ft_memdel((void**)&tb);
	return (ft_itoa(set_assign(begin)));
}
