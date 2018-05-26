/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 09:50:51 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:22 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_move_tolinel(t_line *line, int *val)
{
	char	*str;
	int		i;
	int		try;

	if (!line || !(str = val[4] ? line->line : line->eof))
		return (-1);
	if ((val[6] = tgetnum("co")) <= 0)
		return (-1);
	i = ft_lenline_v(str, val[0]) % val[6];
	while (i > 0)
	{
		try = 3;
		while (try > 0 && ft_move_left(line, val) == -1)
			try--;
		if (try == 0)
			return (-1);
		i--;
	}
	return (1);
}

int		ft_move_toliner(t_line *line, int *val)
{
	char	*str;
	int		i;
	int		try;
	int		to;

	if (!line || !(str = val[4] ? line->line : line->eof))
		return (-1);
	if ((to = tgetnum("co")) <= 0)
		return (-1);
	i = (ft_lenline_v(str, val[0]) % to) + 1;
	while (i < to && str[val[0]] != '\n')
	{
		try = 3;
		while (try > 0 && ft_move_right(line, val) == -1)
			try--;
		if (try == 0)
			return (-1);
		i++;
	}
	return (1);
}
