/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:07:55 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 18:30:25 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		is_incre(t_do_op **b, t_do_op *a)
{
	t_do_op *todel;

	if (!ft_strcmp(a->content, "-") || !ft_strcmp(a->content, "!") ||
			!ft_strcmp(a->content, "+") || !ft_strcmp(a->content, "~"))
	{
		if ((a->prev && !check_op(a->prev->content)))
		{
			if (!check_op(a->next->content))
				return (0);
			unaire(&(*b)->next);
			return (1);
		}
		if (ft_isin(*a->content, "+_"))
			a->next->sign = (a->sign | 1) * (*a->content == '+' ? 1 : -1);
		a->next->is_spec |= !(ft_strcmp(a->content, "~"));
		a->next->is_spec |= !(ft_strcmp(a->content, "!")) * 2;
		unaire(&(*b)->next);
		todel = *b;
		*b = (*b)->next;
		free_op(&todel);
		return (1);
	}
	return (0);
}

int		exe_assign(t_do_op *to_ass, char *str, int value)
{
	static int		(**f_op)(int, int) = 0;
	int				len;
	int				code;
	int				a;
	t_do_op			*to_del[2];

	if (!f_op)
		f_op = f_opget();
	len = ft_strlento(str, '=');
	if (len)
	{
		*str != '=' ? str[len] = '\0' : 0;
		a = get_value(to_ass);
		code = ft_strisin_tab(str, OPE, 0);
	}
	*to_del = to_ass->next;
	to_del[1] = (*to_del)->next;
	free_op(&(*to_del));
	free_op(&to_del[1]);
	return (len ? f_op[code](a, value) : value);
}

char	**all_op(int index)
{
	static char **tb = 0;
	static char **assign = 0;

	if (!tb)
	{
		tb = (char *[40]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=" "&=",
	"^=", "|=", "==", "!=", "<=", ">=", "--", "++", "<<", ">>", "||", "|", "**",
	"&&", "&", "^", "~", "<", ">", "=", "*", "/", "%", "-", "+", "?", ":", 0};
		tb = ft_strtbdup(tb);
	}
	if (!assign)
	{
		assign = (char *[20]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=",
		"^=", "|=", "=", 0};
		assign = ft_strtbdup(assign);
	}
	return (!index ? tb : assign);
}
