/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:05:20 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 18:25:12 by ygarrot          ###   ########.fr       */
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

int		parenth(char **str, int i, char rep, bool recc)
{
	if (!*str)
		return (1);
	while ((*str)[++i])
		if ((*str)[i] == '(')
		{
			while ((*str)[++i])
			{
				if ((*str)[i] == ')' && ((!recc ? (*str)[i] = rep : 0) || 1))
					return (i);
				if ((*str)[i] == '(' && (i = parenth(str, i - 1, rep, 1)) < 0)
					return (-ft_printf("Parenthesis error\n"));
			}
			return (-1);
		}
	return (i);
}
