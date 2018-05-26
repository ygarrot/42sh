/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lentoend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:43:22 by tcharrie          #+#    #+#             */
/*   Updated: 2018/04/20 09:40:38 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_lennline(char *str, int line, int col)
{
	int	i;
	int	c;

	if (!str || (i = 0))
		return (0);
	c = 0;
	while (line && *str)
	{
		if (!(c = (c + 1) % col) || *str == '\n')
			line--;
		if (*str == '\n')
			c = 0;
		if (line || *str != '\n')
			i += ft_lenchar_r(str, 0);
		str += ft_lenchar_r(str, 0);
	}
	return (i);
}
