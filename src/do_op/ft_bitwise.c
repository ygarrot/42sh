/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:53:22 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 18:11:41 by ygarrot          ###   ########.fr       */
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
	return (~a);
}

int		ft_ternary(t_do_op *a, t_do_op *b, int *result)
{
	t_do_op *tmp;
	t_do_op *c;
	int		ret;

	ret = -1;
	c = b->next;
	if ((!a || !b || !c) && error_do_op("error do_op\n"))
		return (0);
	while (c && *c->content != ':')
		c = c->next->next->next->next;
	c = c->next;
	ret = *result;
	*result != -2 ? c->code = -2 : 0;
	a->value = get_value(a);
	b->value = get_value(b);
	c->value = get_value(c);
	tmp = a->value ? b : c;
	*result = tmp->value;
	if (tmp->next && *tmp->next->content == '?' && (*result = -2))
		*result = ft_ternary(tmp, tmp->next->next, result);
	a->is_set = *result;
	return (*result);
}
