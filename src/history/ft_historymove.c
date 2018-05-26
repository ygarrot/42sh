/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_historymove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:32:59 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/07 13:19:58 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_move_tohist(t_line *line, int *val, int dec)
{
	char	*history;

	if (dec == 0 || (val[8] == 0 && dec <= 0) || dec + val[8] < 0 ||
		!(history = ft_history_get(val[8] + dec)))
		return (1);
	if (ft_move_tohome(line, val) == -1)
		return (-1);
	if (val[8] == 0)
		ft_history_cache(ft_strdup((val[4] ? &(line->line)[val[5]] :
			&(line->eof)[val[5]])), CODE_SET);
	if (val[4])
		ft_bzero((void*)(&(line->line)[val[0]]), line->size_line - val[0]);
	else
		ft_bzero((void*)(&(line->eof)[val[0]]), line->size_eof - val[0]);
	tputs(tgetstr("cd", 0), 0, writechar);
	val[9] = ft_printstr(line, history, val);
	val[8] += dec;
	return (val[9]);
}
