/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:05:20 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 10:52:54 by ygarrot          ###   ########.fr       */
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

	if (!str || !brack)
		return (0);
	if (*str == *brack)
		if ((tmp = ft_charchr(brack[1], str)))
			return (tmp);
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

int		skip_bracket(char *str)
{
	int	i;
	int	tmp;

	i = 0;
	if (!str || !*str)
		return (0);
	if (*str == ')')
		return (-1);
	if (*str != '(')
		return (0);
	while (str[++i])
	{
		i += skip_comm(&str[i]);
		if (str[i] == '(')
		{
			if ((tmp = skip_bracket(&str[i])) < 0)
				return (-1);
			else
				i += tmp + 1;
		}
		if (str[i] == ')')
			return (i);
	}
	return (-1);
}
int		check_bracket(char *str)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (str[++i])
	{
		i += skip_comm(&str[i]);
		if ((tmp = skip_bracket(&str[i])) < 0)
		{
			ft_printf("parse error near `()'\n");
			return (-1);
		}
		else
			i += tmp;
	}
	return (0);
}
