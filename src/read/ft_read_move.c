/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:03:52 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 14:21:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_move_left(t_line *line, int *val)
{
	if (!line || !line->line || !val)
		return ;
	if (val[0] > val[5])
		val[0] -= ft_lenchar_l(line->line, val[0]);
}

void	ft_read_move_wordl(t_line *line, int *val)
{
	char	*delim;

	if (!line || !line->line || !val)
		return ;
	if (!(delim = ft_read_delim()))
		return ;
	while (val[0] > val[5] && ft_isin(line->line[val[0]], delim))
		val[0] -= ft_lenchar_l(line->line, val[0]);
	while (val[0] > val[5] && !ft_isin(line->line[val[0] - 1], delim))
		val[0] -= ft_lenchar_l(line->line, val[0]);
}

void	ft_read_move_right(t_line *line, int *val)
{
	if (!line || !line->line || !val)
		return ;
	if (line->line[val[0]])
		val[0] += ft_lenchar_r(line->line, val[0]);
}

void	ft_read_move_wordr(t_line *line, int *val)
{
	char	*delim;

	if (!line || !line->line || !val)
		return ;
	if (!(delim = ft_read_delim()))
		return ;
	while (line->line[val[0]] && !ft_isin(line->line[val[0]], delim))
		val[0] += ft_lenchar_r(line->line, val[0]);
	while (line->line[val[0]] && ft_isin(line->line[val[0]], delim))
		val[0] += ft_lenchar_r(line->line, val[0]);
}

void	ft_read_move_tohome(t_line *line, int *val)
{
	if (val)
		val[0] = val[5];
}
