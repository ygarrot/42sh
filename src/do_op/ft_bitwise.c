/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:53:22 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/18 14:34:11 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
	return(~a);
}
