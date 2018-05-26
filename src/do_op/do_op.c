/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:08:36 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 11:08:36 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

# define A 0
# define O 1
# define B 2
# define RES 3

int		do_op(int *val)
{
	int i;
	static int		(**f_op)(int, int) = 0;

	if (!f_op)
		f_op = f_opget();
	i = -1;
	return (f_op[val[O]](val[A], val[B]));
}

int		is_local(char *str);

int		get_value(char *str)
{
	if (!(ft_occiter2(str, ft_isdigit) < 0))
		return(ft_atoi(str));
	return (is_local(str));
}

int		calc_op(char **op_tb)
{
	int 		i;
	int			is_digit;
	int			is_set[4];
	int			val[4];

	i = -1;
	ft_bzero(&is_set, sizeof(is_set));
	while (op_tb[++i])
	{
		if (!is_set[O] && (val[O] = get_sep(op_tb[i], OPE)) >= 0 && ++is_set[O])
			continue ;
		//ft_printf("RES[%d]A[%d]O[%d]B[%d][%d]%s\n",val[RES],val[A], is_set[O], is_set[B], i, op_tb[i]);
		if (is_set[RES] && (is_set[A] = 1))
			val[A] = val[RES];
		if (!is_set[A] && ++is_set[A])
			val[A] = get_value(op_tb[i]);
		else if (!is_set[O])
			exit(-ft_printf("no op\n"));
		else if (++is_set[B])
			val[A] = get_value(op_tb[i]);
		else
			exit(-ft_printf("invalid\n"));
	}
	return (val[RES]);
}
