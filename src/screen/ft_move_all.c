/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:24:52 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:21 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_move_tohome(t_line *line, int *val)
{
	int	tmp;

	tmp = val[0];
	while (val[0] > val[5])
	{
		ft_move_up(line, val);
		if (tmp == val[0])
			return (-1);
		tmp = val[0];
	}
	return (1);
}

int		ft_move_toend(t_line *line, int *val)
{
	char	*str;
	int		tmp;

	str = (val[4] ? line->line : line->eof);
	tmp = val[0];
	while (str[val[0]])
	{
		ft_move_down(line, val);
		if (tmp == val[0])
			return (-1);
		tmp = val[0];
	}
	return (1);
}

int		ft_move_wordl(t_line *line, int *val)
{
	int	size;
	int	try;

	size = ft_lenword_l(&(val[4] ? line->line : line->eof)[val[5]],
			val[0] - val[5]);
	while (size-- > 0)
	{
		try = 3;
		while (try > 0 && ft_move_left(line, val) == -1)
			try--;
		if (try == 0)
			return (-1);
	}
	return (1);
}

int		ft_move_wordr(t_line *line, int *val)
{
	int	size;
	int	try;

	size = ft_lenword_r(&(val[4] ? line->line : line->eof)[val[5]],
			val[0] - val[5]);
	while (size-- > 0)
	{
		try = 3;
		while (try > 0 && ft_move_right(line, val) == -1)
			try--;
		if (try == 0)
			return (-1);
	}
	return (1);
}
