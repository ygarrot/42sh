/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_reset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:31:06 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/07 13:49:35 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_selected_reset(t_line *line, int *val)
{
	char	*str;
	int		tmp;

	if (!line || !(str = (val[4] ? line->line : line->eof)))
		return (-1);
	tmp = ft_abs(val[2]);
	while (val[2] > 0 && val[2]--)
		if (ft_move_left(line, val) == -1)
			return (-1);
	ft_printf("{whiteblack}%.*s",
			ft_lennchar_r(str, val[0], tmp), &str[val[0]]);
	val[0] += tmp;
	val[2] = 0;
	return (1);
}
