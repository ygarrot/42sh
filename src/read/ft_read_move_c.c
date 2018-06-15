/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_move_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:37:28 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 15:39:35 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_movetohist(t_line *line, int *val, int mov)
{
	char	*str;

	if (!line || !line->line || !val || mov == 0 || val[8] + mov < 0)
		return ;
	if (val[8] == 0)
		ft_history_cache(ft_strdup(&(line->line)[val[1]]), CODE_SET);
	if (!(str = ft_history_get(val[8] + mov)))
		return ;
	if (!(str = ft_strdup(str)))
		return ;
	ft_strdel(&line->line);
	val[5] = 0;
	val[0] = ft_min(val[0], (int)ft_strlen(str));
	if (val[0] < 0)
		val[0] = 0;
	val[1] = 0;
	line->line = str;
}

void	ft_read_move_up(t_line *line, int *val)
{
	int	i;
	int	j;
	int	k;

	if (!line || !line->line || !val)
		return ;
	j = val[0] - ft_lenline_c(line->line, val[0]);
	if (j <= val[5])
	{
		val[0] = val[5];
		return ;
	}
	i = ft_lenline_v(line->line, val[0]);
	val[0] = j;
	j = ft_lenline_v(line->line, val[0]);
	k = ft_lenline_c(line->line, val[0]);
	while (k < val[5])
	{
		j--;
		k += ft_lenchar_r(line->line, k);
	}
	val[0] = k;
	if (j > 0)
		val[0] = k + ft_lennchar_r(line->line, k, ft_min(i, j));
}

void	ft_read_move_down(t_line *line, int *val)
{
	int	i;
	int	k;

	if (!line || !line->line || !val)
		return ;
	i = ft_lenline_v(line->line, val[0]);
	while (line->line[val[0]] && line->line[val[0]] != '\n')
		val[0]++;
	if (!line->line[val[0]])
		return ;
	k = 0;
	while (line->line[val[0]] && line->line[val[0]] != '\n' && k < i)
	{
		k++;
		val[0] += ft_lenchar_r(line->line, val[0]);
	}
}
