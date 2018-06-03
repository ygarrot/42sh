/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:08:36 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/03 14:34:17 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int (**f_opget(void))(int, int)
{
	static int		(*f_op[14])(int, int);
	
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
	return (f_op);
}

int		get_value(t_do_op *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->is_set)
		return (tmp->value);
	tmp->is_set = 1;
	if (ft_str_isdigit(tmp->content))
		return (ft_atoi(tmp->content));
	return (is_local(tmp->content));
}

int		do_op(t_do_op *a, t_do_op *op, t_do_op *b)
{
	static int		(**f_op)(int, int) = 0;

	if (!f_op)
		f_op = f_opget();
	a->value = get_value(a);
	b->value = get_value(b);
	//ft_printf("%s %s %s\n", a->content, op->content, b->content);
	return (f_op[op->code](a ? a->value : 0, b ? b->value : 0));
}

int		is_local(char *str);

