/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:09:36 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:19 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_goto(int x, int y)
{
	int	fx;
	int	fy;
	int	err;

	fx = 0;
	fy = 0;
	err = 0;
	if (ft_getpos(&fx, &fy))
		return (-1);
	if (fy == tgetnum("co"))
		if (tputs(tgetstr("le", 0), 0, writechar) == ERR || ft_getpos(&fx, &fy))
			return (-1);
	fy = (fx < x) ? 1 : fy;
	while (fx > x && fx--)
		err = tputs(tgetstr("up", 0), 0, writechar) == ERR || err;
	while (fx < x && fx++)
		err = tputs(tgetstr("do", 0), 0, writechar) == ERR || err;
	while (fy < y && fy++)
		err = tputs(tgetstr("nd", 0), 0, writechar) == ERR || err;
	while (fy > y && fy--)
		err = tputs(tgetstr("le", 0), 0, writechar) == ERR || err;
	return (err ? -1 : 1);
}
