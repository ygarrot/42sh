/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:53:22 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 13:27:36 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_left_shift(int a, int b)
{
	return (a << b);
}

int		ft_right_shift(int a, int b)
{
	return (a >> b);
}

int		ft_xor(int a, int b)
{
	return (a ^ b);
}

int		ft_bitneg(int a, int b)
{
	(void)b;
	return(~a);
}

int		ft_ternary(t_do_op *a, t_do_op *b, int *result)
{
	t_do_op *tmp;
	t_do_op *c;
	int		ret;

	ret = 4;
	c = b->next;
	if ((!a || !b || !c) && error_do_op("error do_op\n") )
		return (0);
	while (c && *c->content != ':')
	{
		while (--ret > 0)
			if (!(c = c->next) && error_do_op("error do_op\n") 
			&& !(*result = 0))
				return (0);
		//c = c->next->next->next->next;
	}
	c = c->next;
	a->value = get_value(a);
	b->value = get_value(b);
	c->value = get_value(c);
	tmp = a->value ? b : c;
	//ft_printf("%s %s %s\n", a->content, b->content, c->content);
	//ft_printf("%d %d %d\n", a->value, b->value, c->value);
	*result = tmp->value;
	del_ternary(b->next);
	if (tmp->next && *tmp->next->content == '?')
		ft_ternary(tmp, tmp->next->next, result);
	return (ret);
}
