/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_base_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:37:21 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:22 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_move_up_bis(char *str, int *val, int x, int y)
{
	int	tmp;

	if (val[4] && val[5] < val[9] && (val[9]-- || 1))
	{
		val[12] = ft_lenline_v(str, val[9]);
		tmp = (val[12] > val[10]) ? (val[12] - val[10]) : (0);
		if (val[9] - ft_lenline_c(str, val[9]) < val[5])
		{
			val[10] = val[5] - ft_lenline_c(str, val[5]);
			while (tmp > 0 && val[10] < val[5] && tmp--)
				val[10] += ft_lenchar_r(str, val[10]);
		}
		val[11] += (tmp) ? (1 + (tmp > (val[12] % val[6])) +
			(tmp - 1 - (val[12] % val[6])) / val[6]) : (1);
		while (tmp-- > 0)
			val[9] -= ft_lenchar_l(str, val[9]);
		val[12] = 1 + (ft_lenline_v(str, val[9]) % val[6]);
	}
	val[0] -= ft_lenline_col(str, val[0], val[6]);
	ft_move_up_ter(str, val, y);
	while (x-- > 1 && val[11]-- > 0)
		if (tputs(tgetstr("up", 0), STDOUT_FILENO, writechar) == ERR)
			return ;
		else if (val[0] > 0)
			val[0] -= (ft_lenline_col(str, val[0] - 1, val[6]) + 1);
}

/*
** val[11] : Nombre de "up" a realiser
** val[12] : Position finale horizontale
*/

void	ft_move_up_ter(char *str, int *val, int y)
{
	int	tmp;

	while (val[11] > 0 && y > 1)
		if (tputs(tgetstr("le", 0), 0, writechar) == ERR || (y--) < 0)
			return ;
	while (val[11]-- > 0 && val[0] >= 0)
	{
		tputs(tgetstr("sr", 0), STDOUT_FILENO, writechar);
		val[10] = ft_lenline_v(str, val[0] - 1) % val[6];
		tmp = ft_lenline_col(str, val[0] - 1, val[6]) +
			(str[val[0] - 1] != '\n');
		val[0] -= ((str[val[0] - 1] == '\n') + tmp);
		write(1, &(str[val[0]]), tmp);
		while (val[10]-- > 0)
			tputs(tgetstr("le", 0), STDOUT_FILENO, writechar);
	}
	while (y < val[12])
		if (tputs(tgetstr("nd", 0), STDOUT_FILENO, writechar)
				== ERR || (y++) < 0)
			return ;
	while (y-- > val[12])
		tputs(tgetstr("le", 0), STDOUT_FILENO, writechar);
	val[0] = val[9];
}

int		ft_move_down_bis(char *str, int *val, int x, int y)
{
	val[10] = ft_lenline_v(str, val[0]) % val[6];
	while (str[val[0]] && str[val[0]] != '\n' && val[10]++ < val[6])
		val[0] += ft_lenchar_r(str, val[0]);
	val[0] += (str[val[0]] == '\n' && val[10] < val[6]);
	while (x < val[7] && val[11])
	{
		val[11]--;
		if (tputs(tgetstr("do", 0), STDOUT_FILENO, writechar) == ERR)
			return (-1);
		y = 1;
		while (str[val[0]] && str[val[0]] != '\n' && val[10]++ < val[6])
			val[0] += ft_lenchar_r(str, val[0]);
		val[0] += (str[val[0]] == '\n' && val[10] < val[6]);
		val[10] = 0;
	}
	while (val[11] > 0 && y > 1 && y--)
		if (tputs(tgetstr("le", 0), STDOUT_FILENO, writechar) == ERR)
			return (-1);
	return (ft_move_down_ter(str, val, y));
}

int		ft_move_down_ter(char *str, int *val, int y)
{
	int	tmp;

	while (val[11]-- > 0 && !(val[10] = 0))
	{
		tmp = 0;
		if (tputs(tgetstr("sf", 0), STDOUT_FILENO, writechar) == ERR)
			return (-1);
		while (str[val[0] + tmp] &&
			str[val[0] + tmp] != '\n' && val[10] < val[6])
			tmp += ft_lenchar_r(str, val[0] + val[10]++);
		write(1, &str[val[0]], tmp);
		val[0] += tmp + (val[10] < val[6] && str[val[0] + tmp] == '\n');
		while (val[10]-- > 0)
			if (tputs(tgetstr("le", 0), STDOUT_FILENO, writechar) == ERR)
				return (-1);
	}
	while (y < val[12] && y++ > 0)
		if (tputs(tgetstr("nd", 0), STDOUT_FILENO, writechar) == ERR)
			return (-1);
	while (y-- > val[12])
		if (tputs(tgetstr("le", 0), STDOUT_FILENO, writechar) == ERR)
			return (-1);
	val[0] = val[9];
	return (1);
}
