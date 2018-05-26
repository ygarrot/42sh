/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 13:32:30 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:20 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** Donne le nombre de char dans la chaine avant le debut de ligne
*/

int		ft_lenline_c(char *str, int pos)
{
	int	i;

	if (!str || pos <= 0 || str[pos - 1] == '\n')
		return (0);
	while (pos >= 0 && (str[pos] & '\xc0') == '\x80')
		pos--;
	pos--;
	i = 0;
	while (pos - i >= 0 && str[pos - i] != '\n')
		i++;
	return (i);
}

/*
** Donne le nombre de char affichés avant le debut le ligne
*/

int		ft_lenline_v(char *str, int pos)
{
	int	i;

	if (!str || pos <= 0 || str[pos - 1] == '\n')
		return (0);
	i = 0;
	while (pos >= 0 && (str[pos] & '\xc0') == '\x80')
		pos--;
	pos--;
	while (pos >= 0 && str[pos] != '\n')
	{
		if ((str[pos] & '\xc0') == '\xc0' || (str[pos] & '\x80') == 0)
			i++;
		pos--;
	}
	return (i);
}

/*
** str[pos - return] est le premier charactere de la ligne visuel
*/

int		ft_lenline_col(char *str, int pos, int col)
{
	int	i;
	int	j;

	if (!str || pos <= 0 || str[pos - 1] == '\n')
		return (0);
	i = ft_lenline_v(str, pos) % col;
	j = 0;
	while (pos - j >= 0 && i > 0)
	{
		i--;
		j += ft_lenchar_l(str, pos - j);
	}
	return (j);
}
