/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 13:32:18 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 13:09:00 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** Move left of one
** Manages scrolling & co
*/

int		ft_move_left(t_line *line, int *val)
{
	int	ret;

	ret = 1;
	if ((val[6] = tgetnum("co")) <= 0 || !tgetstr("up", 0) || !tgetstr("nd", 0)
			|| !tgetstr("le", 0) || val[0] <= val[5])
		return (-1);
	if (ft_getpos(&val[9], &val[10]))
		return (-1);
	if (val[9] == 1 && val[10] == 1)
		ret = ft_scroll_down(line, val);
	else if (val[10] == 1)
	{
		if (tputs(tgetstr("up", 0), STDOUT_FILENO, writechar) == ERR)
			return (-1);
		val[9] = ft_lenline_v((val[4] ? line->line : line->eof),
					val[0] - 1) % val[6];
		while (val[9]--)
			if (tputs(tgetstr("nd", 0), STDOUT_FILENO, writechar) == ERR)
				ret = -1;
	}
	else if (tputs(tgetstr("le", 0), STDOUT_FILENO, writechar) == ERR)
		ret = -1;
	val[0] -= ft_lenchar_l(val[4] ? line->line : line->eof, val[0]);
	return (ret);
}

int		ft_move_right(t_line *line, int *val)
{
	int	ret;

	ret = 1;
	if ((val[6] = tgetnum("co")) <= 0 || !tgetstr("do", 0) || !tgetstr("le", 0))
		return (-1);
	if ((val[4] ? line->line : line->eof)[val[0]] == 0 || (val[7] =
				tgetnum("li")) <= 0 || ft_getpos(&(val[9]), &(val[10])))
		return (-1);
	if (val[9] == val[7] && (val[10] == val[6] || (val[4] ?
		line->line[val[0]] : line->eof[val[0]]) == '\n'))
		ret = ft_scroll_up(line, val);
	else if (val[10] == val[6] || (val[4] ? line->line[val[0]] :
				line->eof[val[0]]) == '\n')
	{
		if (tputs(tgetstr("do", 0), STDOUT_FILENO, writechar) == ERR)
			ret = -1;
	}
	else if (tputs(tgetstr("nd", 0), STDOUT_FILENO, writechar) == ERR)
		ret = -1;
	val[0] += ft_lenchar_r(val[4] ? line->line : line->eof, val[0]);
	return (ret);
}

/*
** Dans un premier temps déterminer la coordonnée horizontale de la destination
** & le nombre de lignes à remonter.
** Puis y aller étape par étape en commençant par aller à gauche si besoin
** de scroll
*/

void	ft_move_up(t_line *line, int *val)
{
	char	*str;
	int		x;
	int		y;

	if (!(str = (val[4] ? line->line : line->eof)) || ft_getpos(&x, &y))
		return ;
	if ((val[6] = tgetnum("co")) <= 0 || !tgetstr("up", 0) ||
		!tgetstr("le", 0) || !tgetstr("kr", 0))
		exit(3);
	if ((val[7] = tgetnum("li")) <= 0)
		exit(4);
	val[10] = ft_lenline_v(str, val[0]);
	val[11] = val[10] / val[6];
	if ((val[9] = val[0] - ft_lenline_c(str, val[0])) < val[5])
		val[9] = val[5];
	if (val[9] == val[5])
		val[10] += ft_lenline_v(str, val[5]);
	if (val[9] == val[5])
		val[11] -= ft_lenline_v(str, val[5]) / val[6];
	if (val[4] == 0)
		val[12] = 1;
	else if (val[5] == val[9])
		val[12] = (ft_lenline_v(str, val[5]) % val[6]) + 1;
	ft_move_up_bis(str, val, x, y);
}

int		ft_move_down(t_line *line, int *val)
{
	char	*str;
	int		x;
	int		y;

	if ((val[6] = tgetnum("co")) <= 0 || !tgetstr("do", 0) ||
		!tgetstr("le", 0) || ft_getpos(&x, &y))
		return (-1);
	if ((val[7] = tgetnum("li")) <= 0)
		return (-1);
	str = (val[4]) ? (line->line) : (line->eof);
	val[9] = val[0] + ft_strlento(&str[val[0]], '\n');
	val[11] = (ft_lenline_v(str, val[9]) / val[6]) - (ft_lenline_v(str,
		val[0]) / val[6]);
	val[10] = ft_lenline_v(str, val[0]) - ((val[0] -
		ft_lenline_c(str, val[0])) < val[5] ? ft_lenline_v(str, val[5]) : 0);
	if (str[val[9]] == '\n' && val[9]++)
	{
		val[9] += ft_lennchar_r(str, val[9], ft_min(ft_strlento(&str[val[9]],
			'\n'), val[10]));
		val[11] += 1 + (ft_lenline_v(str, val[9]) / val[6]);
	}
	val[12] = (ft_lenline_v(str, val[9]) % val[6]) + 1;
	return (ft_move_down_bis(str, val, x, y));
}
