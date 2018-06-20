/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_backslashn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:03:59 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 16:49:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	replace_backslashn(char **str)
{
	int tmp;
	int i;

	i = -1;
	while ((*str)[++i])
	{
		i += skip_comm(&(*str)[i]);
		if ((*str)[i] == '\n')
		{
			tmp = i - 1;
			while (tmp >= 0 && (*str)[tmp] == ' ')
				tmp--;
			if (get_sep(&(*str)[tmp], SEP) >= 0)
				ft_strcpy(&(*str)[i], &(*str)[i + 1]);
		}
	}
}

int		skip_br(char *str, int i)
{
	int tmp;

	if (!str || !*str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '(')
		{
			while (str[++i])
			{
				if (str[i] == ')')
					return (i);
				if (str[i] == '(' && (tmp = skip_br(&str[i], -1)) < 0)
					return (ft_error("Parenthesis error", 0));
				else if (str[i] == '(')
					i += tmp;
			}
			return (-1);
		}
	}
	return (0);
}

int		br_util(char *str)
{
	int		i;
	char	q;

	i = 0;
	if (!str || !*str)
		return (0);
	if ((ft_isin(str[i], QUOTES) && (q = str[i++])))
	{
		while (str[i] && str[i++] != q)
		{
			i += (str[i] == '\\' && str[i + 1]);
			if (!str[i])
				return (0);
		}
	}
	if (str[i] == '\\')
		i += str[i + 1] ? 2 : 1;
	return (i);
}
