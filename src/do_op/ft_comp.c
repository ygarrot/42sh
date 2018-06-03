/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 15:20:06 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/03 15:59:45 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int	ft_comp_supe(int a, int b)
{
	return (a >= b);
}

int	ft_comp_inf(int a, int b)
{
	return (a < b);
}

int	ft_comp_sup(int a, int b)
{
	return (a > b);
}

int	ft_comp(int a, int b)
{
	return (a == b);
}

int	ft_comp_neg(int a, int b)
{
	return (a != b);
}
