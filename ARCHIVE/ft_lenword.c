/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:05:24 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 10:53:15 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int			ft_lenword_r(char *str, int pos)
{
	int	i;
	int	sep;
	int	bl;
	int	bq;

	i = 0;
	bq = ft_separator_active(str, pos, &sep, &bl);
	if (!sep && !bl && ft_isin(str[pos], "&|<>;"))
		return (1 + (str[pos] != ';' && str[pos] == str[pos + 1]));
	if (!sep && !bl && ft_isin(str[pos], " \n"))
	{
		while (str[pos] && ft_isin(str[pos], " \n") && ++i)
			pos += ft_lenchar_r(str, pos);
		return (i);
	}
	while (str[pos] && (bl || sep || !ft_isin(str[pos], ENDWORD)))
	{
		ft_separator(str[pos], &sep, &bl, &bq);
		i++;
		pos += ft_lenchar_r(str, pos);
	}
	return (i);
}

static void	ft_lenword_left(char *str, int pos, int *i, int *mov)
{
	int		j;

	*mov = 0;
	j = ft_isin(str[*i], "l|&<>;");
	if (j && str[*i + 1] == str[*i])
		j++;
	*i += j;
	if (j && *i >= pos)
		*mov = j;
	if (j)
		return ;
	while (*i < pos && str[*i] && (ft_isin(str[*i], " \n")))
	{
		*mov += 1;
		*i += ft_lenchar_r(str, *i);
	}
}

int			ft_lenword_l(char *str, int pos)
{
	int	mov;
	int	i;
	int	bl;
	int	sep;
	int	bq;

	bq = 0;
	if (!str || !pos || (i = 0))
		return (0);
	bl = 0;
	sep = 0;
	while ((i < pos && str[i]) && !(mov = 0))
	{
		while (i < pos && str[i] && (sep || bl || !ft_isin(str[i], ENDWORD)))
		{
			mov++;
			ft_separator(str[i], &sep, &bl, &bq);
			i += ft_lenchar_r(str, i);
		}
		if (i >= pos || !str[i])
			break ;
		ft_lenword_left(str, pos, &i, &mov);
	}
	return (mov ? mov : 1);
}
