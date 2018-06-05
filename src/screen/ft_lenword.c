/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:05:24 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/27 14:14:40 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int			ft_lenword_r(char *str, int pos)
{
	int	mov;

	if (!str || pos < 0)
		return (0);
	mov = 0;
	while (str[pos] && !ft_isin(str[pos], ENDWORDVIS))
	{
		mov++;
		pos += ft_lenchar_r(str, pos);
	}
	while (str[pos] && ft_isin(str[pos], ENDWORDVIS))
	{
		mov++;
		pos += ft_lenchar_r(str, pos);
	}
	return (mov);
}

int			ft_lenword_l(char *str, int pos)
{
	int	mov;

	if (!str || pos <= 0)
		return (0);
	if (!str[pos])
		pos--;
	else
		pos -= ft_lenchar_l(str, pos);
	if (pos <= 0)
		return (1);
	mov = 0;
	while (pos > 0 && ft_isin(str[pos], ENDWORDVIS))
	{
		mov++;
		pos -= ft_lenchar_l(str, pos);
	}
	while (pos > 0 && !ft_isin(str[pos], ENDWORDVIS))
	{
		mov++;
		pos -= ft_lenchar_l(str, pos);
	}
	if (pos == 0 && !ft_isin(str[pos], ENDWORDVIS))
		mov++;
	return (mov);
}
