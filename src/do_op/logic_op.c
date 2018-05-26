/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:33:00 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/18 15:15:14 by ygarrot          ###   ########.fr       */
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

