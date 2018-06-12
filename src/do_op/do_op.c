/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:08:36 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 18:11:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	del_ternary(t_do_op *c)
{
	t_do_op *tmp;
	t_do_op *to_del;

	if (!c && error_do_op("error do_op : del_ternary\n"))
		return ;
	while (c && c->is_set)
	{
		tmp = c;
		while (*tmp->content == '?')
		{
			c = c->next->next->next->next;
			while (tmp != c)
			{
				to_del = tmp;
				tmp = tmp->next;
				free_op(to_del);
			}
		}
		tmp = c->next->next;
		free_op(c->next);
		free_op(c);
		c = tmp;
	}
}

int (**f_opget(void))(int, int)
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

int		get_value(t_do_op *tmp)
{
	char *s;
	int i;

	if (!tmp)
		return (error_do_op("error do_op\n"));
	if (tmp->is_set)
		return (tmp->value * (tmp->sign | 1));
	tmp->is_set = 1;
	if (ft_str_isdigit(tmp->content))
		return (ft_atoi(tmp->content));
	s = ft_variablepars(tmp->content);
	i = ft_atoi(s);
	ft_memdel((void**)&s);
	if (tmp->is_inc)
		set_op_variable(tmp->content, i + tmp->is_inc);
	return (i * (tmp->sign | 1));
}

int		do_op(t_do_op *a, t_do_op *op, t_do_op *b)
{
	static int		(**f_op)(int, int) = 0;

	if (!f_op)
		f_op = f_opget();
	
	//if (!a || !op || !b)
	//	return (error_do_op("error do_op\n"));
	if (!ft_strcmp(op->content, "?"))
		return (ft_ternary(a, b));
	a->value = get_value(a);
	b->value = get_value(b);
	op->code = get_sep(op->content, OPE) ;
	op->code < 0 ? op->code = get_sep(op->content, COMP) : 0;
	return (f_op[op->code](a ? a->value : 0, b ? b->value : 0));
}
