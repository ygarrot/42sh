/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:53:22 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 12:29:21 by ygarrot          ###   ########.fr       */
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

int		ft_ternary(t_do_op *a, t_do_op *b)
{
	t_do_op *tmp;
	t_do_op *c;
	int	ret;

	c = b->next;
	while (c && *c->content != ':')
		c = c->next->next->next->next;
	c = c->next;
	a->value = get_value(a);
	b->value = get_value(b);
	c->value = get_value(c);
	tmp = a->value ? b : c;
	//ft_printf("%s %s %s\n", a->content, b->content, c->content);
	//ft_printf("%d %d %d\n", a->value, b->value, c->value);
	ret = tmp->value;
	if (tmp->next && *tmp->next->content == '?')
		ret = ft_ternary(tmp, tmp->next->next);
	del_ternary(b->next);
	return (ret);
}
