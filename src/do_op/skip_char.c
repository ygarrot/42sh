/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:05:20 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/02 17:26:12 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		skip_char(char *str, char *to_skip)
{
	int i;

	i = -1;
	if (!str || !to_skip)
		return (0);
	while (str[++i] && ft_isin(str[i], to_skip))
		;
	return (i);
}

int		bracket(char *str, char *brack)
{
	int		tmp;
	int		i;

	i = -1;
	if (!str || !brack)
		return (0);
	if (str[i] == *brack)
		if ((tmp = ft_charchr(brack[1], &str[i])))
			return (tmp < 0 ? 0 : i + tmp);
	return (0);
}

int		ft_occiter2(char *str, int (*f)(int))
{
	int	i;

	i = 0;
	if (!str || !f)
		return (0);
	while (str[i])
	{
		if (!f(str[i]))
			return (-1);
		i++;
	}
	return (i);
}
