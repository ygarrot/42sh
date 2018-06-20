/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:07:55 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:57:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int			is_crement(char **tb)
{
	if (ft_strcmp(*tb, "++") && ft_strcmp(*tb, "--"))
		return (1);
	return (!ft_str_isdigit(tb[1]));
}

static int	(**f_opget(void))(int, int)
{
	static int		(*f_op[20])(int, int);

	f_op[0] = ft_left_shift;
	f_op[1] = ft_right_shift;
	f_op[2] = ft_log_or;
	f_op[3] = ft_log_and;
	f_op[4] = ft_power;
	f_op[6] = ft_and;
	f_op[5] = ft_or;
	f_op[7] = ft_xor;
	f_op[8] = ft_bitneg;
	f_op[9] = ft_summ;
	f_op[10] = ft_sub;
	f_op[11] = ft_div;
	f_op[12] = ft_mult;
	f_op[13] = ft_mod;
	f_op[14] = ft_comp_infe;
	f_op[15] = ft_comp_supe;
	f_op[16] = ft_comp_inf;
	f_op[17] = ft_comp_sup;
	f_op[18] = ft_comp;
	f_op[19] = ft_comp_neg;
	return (f_op);
}

int			is_incre(t_do_op **b, t_do_op *a)
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
		if (ft_isin(*a->content, "+-"))
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

int			exe_assign(t_do_op *to_ass, char *str, int value)
{
	static int		(**f_op)(int, int) = 0;
	int				len[2];
	int				a;
	char			**ope;
	t_do_op			*to_del[2];

	ope = (char *[16]){"<<", ">>", "||", "&&", "**",
		"|", "&", "^", "~", "+", "-", "/", "*", "%", 0};
	if (!f_op)
		f_op = f_opget();
	*len = ft_strlento(str, '=');
	if (*len)
	{
		*str != '=' ? str[*len] = '\0' : 0;
		a = get_value(to_ass);
		len[1] = ft_strisin_tab(str, ope, 0);
	}
	*to_del = to_ass->next;
	to_del[1] = (*to_del)->next;
	free_op(&(*to_del));
	free_op(&to_del[1]);
	return (*len ? f_op[len[1]](a, value) : value);
}

char		**all_op(int index)
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
		mallcheck(assign = ft_strtbdup(assign));
	}
	if (index == -1)
	{
		ft_free_dblechar_tab(tb);
		ft_free_dblechar_tab(assign);
		tb = 0;
		assign = 0;
		return (NULL);
	}
	return (!index ? tb : assign);
}
