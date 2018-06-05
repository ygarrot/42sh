/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 15:24:59 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/03 16:36:18 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_erase(t_line *line, int *val)
{
	if (ft_move_left(line, val) == -1)
		return (-1);
	return (ft_delete(line, val));
}

int		ft_nerase(t_line *line, int *val, int n)
{
	int	i;

	i = 0;
	while (i < n && val[0] > val[5] && ft_move_left(line, val) != -1)
		i++;
	return (ft_ndelete(line, val, i));
}

int		ft_delete(t_line *line, int *val)
{
	char	*str;

	if (!(str = (val[4]) ? (line->line) : (line->eof)))
		return (-1);
	if ((val[9] = val[0] + ft_strlen(&str[val[0]])) == 0)
		return (1);
	if (val[9] < 0)
		return (-1);
	val[10] = val[0];
	val[11] = val[10] + ft_lenchar_r(str, val[10]);
	while (val[10] < val[9])
		str[val[10]++] = str[val[11]++];
	return (ft_printinsert(line, val));
}

int		ft_ndelete(t_line *line, int *val, int n)
{
	char	*str;

	if (!(str = (val[4]) ? (line->line) : (line->eof)))
		return (-1);
	n = ft_min(ft_lennchar_r(str, val[0], n), (int)ft_strlen(&str[val[0]]));
	if (n <= 0)
		return (0);
	if ((val[9] = val[0] + ft_strlen(&str[val[0]])) == 0)
		return (1);
	val[10] = val[0];
	while (val[10] + n < val[9])
	{
		str[val[10]] = str[val[10] + n];
		val[10]++;
	}
	while (val[10] <= val[9])
		str[val[10]++] = 0;
	return (ft_printinsert(line, val));
}
