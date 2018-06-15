/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_move_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:21:53 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 14:37:18 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_move_tolinel(t_line *line, int *val)
{
	if (!line || !line->line || !val)
		return ;
	while (val[0] > val[5] && line->line[val[0] - 1] != '\n')
		val[0]--;
}

void	ft_move_toend(t_line *line, int *val)
{
	if (!line || !line->line || !val)
		return ;
	val[0] = (int)ft_strlen(line->line);
}

void	ft_read_move_toliner(t_line *line, int *val)
{
	if (!line || !line->lien || !val)
		return ;
	while (line->line[val[0]] && line->line[val[0]] != '\n')
		val[0]++;
	if (line->line[val[0]] && line->line[val[0]] == '\n')
		val[0]++;
}

void	ft_read_erase(t_line *line, int *val)
{
	if (!line || !line->line || !val || val[0] == val[5])
		return ;
	ft_read_move_left(line, val);
	ft_read_delete(line, val);
}

void	ft_read_delete(t_line *line, int *val)
{
	int	i;
	int	j;

	if (!line || !line->line || !val || !line->line[val[0]])
		return ;
	i = val[0] + ft_lenchar_r(line->line, val[0]);
	j = val[0];
	while (line->line[i])
		line->line[j++] = line->line[i++];
	line->line[j] = 0;
}
