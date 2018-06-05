/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:34:36 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/25 15:18:36 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_getpos_a(int *x, int *y, char *buff, int re)
{
	*x = 0;
	*y = 0;
	buff[re++] = 0;
	while (buff[re] && (buff[re] < 48 || buff[re] > 57))
		re++;
	while (buff[re] >= 48 && buff[re] <= 57)
		*x = (*x) * 10 + (buff[re++]) - '0';
	if (buff[re++] != ';')
	{
		ft_addtofd(buff, STDIN_FILENO);
		ft_addtofd(&buff[re - 1], STDIN_FILENO);
		return (-1);
	}
	while (buff[re] >= 48 && buff[re] <= 57)
		*y = (*y) * 10 + (int)(buff[re++]) - '0';
	ft_addtofd(&buff[re + 1], STDIN_FILENO);
	ft_addtofd(buff, STDIN_FILENO);
	ft_strdel(&buff);
	return (0);
}

int			ft_getpos(int *x, int *y)
{
	char	*buff;

	if (!x || !y || !write(STDOUT_FILENO, "\33[6n", 4))
		return (-1);
	if (!(buff = ft_readtostr("\33[", 'R', STDIN_FILENO, 100)))
	{
		ft_errorlog("Failed to get the cursor position on screen");
		return (-1);
	}
	return (ft_getpos_a(x, y, buff, ft_strinstr(buff, "\33[")));
}
