/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scroll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:14:47 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:24 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_scroll_down(t_line *line, int *val)
{
	if (!tgetstr("sr", 0))
		return (-1);
	if (tputs(tgetstr("sr", 0), 0, writechar) == ERR)
		return (-1);
	val[0] -= ft_lenchar_l(val[4] ? line->line : line->eof, val[0]);
	val[9] = ft_lenline_v(val[4] ? line->line : line->eof, val[0]) % val[6];
	val[10] = val[0];
	if ((val[11] = (val[9] + 1 == val[6] &&
			(val[4] ? line->line : line->eof)[val[0]] != '\n')))
	{
		val[10] += ft_lenchar_r(val[4] ? line->line : line->eof, val[0]);
		val[0] += ft_lenchar_r(val[4] ? line->line : line->eof, val[0]);
		val[9]++;
	}
	while (val[9]--)
		val[10] -= ft_lenchar_l(val[4] ? line->line : line->eof, val[10]);
	write(1, (val[4] ? &(line->line[val[10]]) : &(line->eof[val[10]])),
			val[0] - val[10]);
	if (!val[11])
		val[0] += ft_lenchar_r(val[4] ? line->line : line->eof, val[0]);
	return (1);
}

int		ft_scroll_up(t_line *line, int *val)
{
	char	*str;

	str = (val[4] ? line->line : line->eof);
	if (!str || ft_getpos(&(val[9]), &(val[10])))
		return (-1);
	while (val[10]-- > 1)
		if (tputs(tgetstr("le", 0), 0, writechar) == ERR)
			return (-1);
	if (tputs(tgetstr("sf", 0), 0, writechar) == ERR)
		return (-1);
	val[9] = val[0] + (str[val[0]] == '\n');
	val[10] = 0;
	val[11] = 0;
	while (val[10] < val[6] && str[val[9] + val[11]] != '\n' &&
			str[val[9] + val[11]])
	{
		val[11] += ft_lenchar_r(str, val[9] + val[11]);
		val[10]++;
	}
	write(1, &(str[val[9]]), val[11]);
	while (val[10]--)
		if (tputs(tgetstr("le", 0), 0, writechar) == ERR)
			return (-1);
	return (1);
}
