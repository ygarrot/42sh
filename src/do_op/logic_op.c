/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:33:00 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/03 16:49:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_log_and(int a, int b)
{
	return (a && b);
}

int		ft_log_or(int a, int b)
{
	return (a || b);
}

int		ft_or(int a, int b)
{
	return (a | b);
}

int		ft_and(int a, int b)
{
	return (a & b);
}

int	ft_comp_infe(int a, int b)
{
	return (a <= b);
}
