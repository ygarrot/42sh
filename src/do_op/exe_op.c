/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 15:43:55 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 18:19:23 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		pre_op(t_do_op **list)
{
	if (!list)
		return (error_do_op("error do_op no op pre_op\n"));
	if (*(*list)->content == '(')
	{
		(*list)->value = ft_atoi(parse_op((*list)->content));
		(*list)->is_set = 1;
		return (1);
	}
	if (unaire(list))
		return (1);
	if (!(*list)->next)
		return (error_do_op("error do_op pre_op next\n"));
	return (del_after_exec(list));
}

int		if_function(t_do_op **beg, int status)
{
	t_do_op *list;

	if (!(list = *beg))
		return (error_do_op("error do_op if_function\n"));
	if ((status == 0 && (*list->content == '('
					|| get_sep(list->content, CREMENT) >= 0)) ||
			(status == 1 && (!ft_strcmp(list->content, "--")
							|| !ft_strcmp(list->content, "++"))) ||
			(status == 2 && (!ft_strcmp(list->content, "-")
							|| !ft_strcmp(list->content, "+"))) ||
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
			(status == 13 && !ft_strcmp(list->content, "&&")) ||
			(status == 14 && !ft_strcmp(list->content, "||")) ||
			(status == 15 && !ft_strcmp(list->content, "?")))
		return (pre_op(beg));
	return (1);
}

int		*the_order(t_do_op **begin)
{
	int			i;
	static int	ret;
	t_do_op		*list;

	i = -1;
	while (*begin && (*begin)->next && ++i < 17)
	{
		list = *begin;
		while (list)
		{
			if (if_function(&list, i) < 0)
				return (NULL);
			list && !list->prev ? *begin = list : 0;
			list ? list = list->next : 0;
		}
	}
	if (*begin)
		!(*begin)->is_set ? (*begin)->value = get_value(*begin) : 0;
	ret = *begin ? (*begin)->value : 0;
	free_do_op(begin);
	return (&ret);
}

char	*set_assign(t_do_op *list)
{
	int		*ret;

	if (!list && error_do_op("error do_op set_assign\n"))
		return (NULL);
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if (get_sep(list->content, all_op(1)) >= 0
				&& ft_strcmp(list->content, "=="))
		{
			if (!(ret = the_order(&list->next)))
				return (NULL);
			list = list->prev;
			list->value = exe_assign(list, list->next->content, *ret);
			set_op_variable(list->content, list->value);
			list->is_set = 1;
		}
		list->prev ? list = list->prev : 0;
	}
	if (!(ret = the_order(&list)))
		return (NULL);
	return (ft_itoa(*ret));
}

char	*exec_op(char **tb)
{
	t_do_op		*list;
	t_do_op		*begin;
	int			i;

	if (!tb)
		return (NULL);
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
	begin_op(&begin);
	ft_memdel((void**)&tb);
	return (set_assign(begin));
}
