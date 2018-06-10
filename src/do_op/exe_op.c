/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 15:43:55 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 12:47:32 by ygarrot          ###   ########.fr       */
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

t_do_op	*pre_op(t_do_op *list)
{
	t_do_op *tmp;

	if (*list->content == '(')
	{
		list->value = ft_atoi(parse_op(list->content));
		list->is_set = 1;
		return (list);
	}
	tmp = list->next->next;
	list->prev->value = do_op(list->prev, list, list->next);
	list = list->prev;
	free_op(list->next->next);
	free_op(list->next);
	list->is_set = 1;
	list->next = tmp;
	//ft_printf("[%d]\n", list->value);
	return (list);
}

t_do_op	*if_function(t_do_op *list, int status)
{
	if ((status == 0 && (*list->content == '('  
					|| get_sep(list->content, OP_CREMENT) >= 0))||
			(status == 1 && (!ft_strcmp(list->content, "--") || !ft_strcmp(list->content, "++"))) ||
			/*(status == 2 && (!ft_strcmp(list->content, "-") || !ft_strcmp(list->content, "+"))) ||*/
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
		list = pre_op(list);
	return (list);
}

int	the_order(t_do_op *begin)
{
	int i;
	t_do_op *list;

	i = -1;
# define ASSIGN (char *[14]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=", "="}
	while (begin && (begin->next || !begin->is_set) && ++i < 17)
	{
		list = if_function(begin, i)->next;
		while (list)
		{
			list = if_function(list, i);
			list ? list = list->next : 0;
		}
	}
	!begin->is_set ? begin->value = ft_atoi(begin->content) : 0;
	begin->is_set = 1;
	return (begin ? begin->value : 0);
}

int	set_assign(t_do_op *list)
{
	char *tmp;

	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if (get_sep(list->content, ASSIGN) >= 0)
		{
			list->prev->value = the_order(list->next);
			list->next ? free_op(list->next) : 0;
			list = list->prev;
			tmp = ft_itoa(list->value);
			tmp = ft_implode("=", list->content, tmp);
			free_op(list->next);
			//ft_printf("%s\n", tmp);
			ft_variable_builtin(tmp);
			ft_printf("%s\n", ft_variablepars(tmp));
			list->is_set = 1;
			ft_memdel((void**)&tmp);
		}
		list->prev ? list = list->prev : 0;
	}
	//if (!list->next)
	//	ft_printf("%d\n", list->value);
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
//		ft_printf("{red}%s %d{reset}\n", list->content, list->code);
		list = list->next;
	}
	ft_memdel((void**)&tb);
	return (ft_itoa(set_assign(begin)));
}
