/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:05:24 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 13:17:59 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static int	ft_lenword_left_bq(char *str, int to, int *mov, int *sep)
{
	int		i;

	*mov = 0;
	if (to <= (i = (*str == '`')))
		return (i);
	while (i < to && ft_isin(str[i], " \n"))
		i++;
	*mov = 0;
	if (i > 1)
		return (i);
	while (i < to && ft_isin(str[i], "<>&|;"))
		i++;
	*mov = 0;
	if (i > 1)
		return (i);
	sep[2] = '`';
	while (i < to && sep[2] && (sep[0] || sep[1] ||
			!ft_isin(str[i], " \n<>&|;")))
	{
		ft_separator(str[i], sep, &sep[1], &sep[2]);
		i += ft_lenchar_r(str, i);
	}
	*mov = (sep[2]) ? (i - 1) : (0);
	return (i);
}

static int	ft_lenword_left_sp(char *str, int to, int *mov)
{
	int	i;

	i = 0;
	*mov = 0;
	if (ft_isin(str[i], "<>|&;"))
	{
		while (i < to && ft_isin(str[i], "<>|&;"))
			i++;
		return (i);
	}
	while (i < to && ft_isin(str[i], " \n"))
		i++;
	return (i);
}

static int	ft_lenword_left_n(char *str, int to, int *mov, int *sep)
{
	int	i;

	i = 0;
	while (i < to && (sep[0] || sep[1] || !ft_isin(str[i], "<>&|;` \n")))
	{
		ft_separator(str[i], sep, &sep[1], 0);
		i += ft_lenchar_r(str, i);
	}
	*mov = (i);
	return (i);
}

int			ft_completion_startpos(char *str, int pos)
{
	int	mov;
	int	sep[3];
	int	i;

	if (!str || pos <= 0 || ft_strlen(str) < (size_t)pos)
		return (0);
	i = 0;
	ft_bzero((void*)sep, sizeof(sep));
	while (i < pos && !(mov = 0))
	{
		if (sep[0] == 0 && sep[1] == 0 && (str[i] == '`' || sep[2]))
			i += ft_lenword_left_bq(&str[i], pos - i, &mov, sep);
		else if (ft_isin(str[i], " \n&|<>;") && !sep[0] && !sep[1])
			i += ft_lenword_left_sp(&str[i], pos - i, &mov);
		else
			i += ft_lenword_left_n(&str[i], pos - i, &mov, sep);
		if (i >= pos)
			return (mov);
		if (i < 0)
			return (0);
	}
	return (mov);
}
