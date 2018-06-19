/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:05:15 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 13:21:08 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_lennchar_l(char *str, int pos, int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i += ft_lenchar_l(str, pos - i);
		n--;
	}
	return (i);
}

int		ft_lennchar_r(char *str, int pos, int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i += ft_lenchar_r(str, pos + i);
		n--;
	}
	return (i);
}
