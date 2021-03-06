/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:06:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:16:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		check_classic(char **tb, int *i)
{
	int		is_op;

	if (tb[*i] && ft_mcharchr(tb[*i], "-~+") >= 0 && tb[*i][1] != '=' && ++*i)
		return (tb[*i] && is_crement(&tb[*i - 1]) ? check_classic(tb, i) : 0);
	if (!tb[*i] || (!(is_op = check_op(tb[*i])) && !tb[++*i]))
		return (1);
	if (is_op || !(is_op = check_op(tb[*i])))
		return (0 & ft_error("operator expected", 0));
	else if (is_op)
	{
		if (get_sep(tb[*i], all_op(1)) >= 0
			&& tb[*i][0] != '=' && ((i - 1) < 0 || ft_str_isdigit(tb[*i - 1])))
			return (0 & ft_error("lvalue required", 0));
		if (ft_isin(*tb[*i], ":?") && (--*i || 1))
			return (1);
		if ((get_sep(tb[*i], CREMENT) >= 0
			|| (tb[*i] && tb[*i + 1] && ft_isin(*tb[*i + 1], "+-~"))) && ++*i)
			return (check_classic(tb, i));
		else if (!check_op(tb[++*i]) && !check_op(tb[*i]))
			return (check_classic(tb, i));
		return (0 & ft_error("arithmetic error", 0));
	}
	return (is_op && get_sep(tb[*i], CREMENT) >= 0 ?
	check_classic(tb, i) : 0 & ft_error("no operator", 0));
}

int		check_op(char *str)
{
	if (!str)
		return (-1);
	if (get_sep(str, all_op(0)) >= 0)
		return (1);
	return (0);
}

int		check_ternaries(char **tb, int *i)
{
	if (check_op(tb[*i]))
		return (1);
	if (!tb[++*i] || *tb[*i] != '?' || check_op(tb[++*i]) || !tb[*i + 1])
		return (0 & ft_error(TERN, 0));
	if (*tb[*i + 1] == '?')
	{
		if (!(check_ternaries(&tb[*i - 2], i)))
			return (0 & ft_error(TERN, 0));
	}
	if (!check_classic(tb, i))
		return (0 & ft_error(TERN, 0));
	if (!tb[*i] || *tb[++*i] != ':')
		return (0 & ft_error(TERN, 0));
	++*i;
	return (tb[*i] ? check_classic(tb, i) : 0 & ft_error(TERN, 0));
}

int		check_all(char **tb)
{
	int			i;
	char		**all;

	i = -1;
	all = all_op(0);
	while (tb[++i])
	{
		if (parenth(&tb[i], -1, '\0', 0) < 0)
			return (0);
		if (!check_classic(tb, &i))
			return (0);
		if (tb[i] && !check_ternaries(tb, &i))
			return (0);
		if (!tb[i])
			return (1);
	}
	return (1);
}

char	*parse_op(char *str)
{
	char	**tb;
	char	*ret;

	str[ft_strlen(str) - 1] = '\0';
	ft_strcpy(str, &str[1]);
	tb = ft_custom_split(str, all_op(0), 0);
	if (!tb || !check_all(tb))
	{
		all_op(-1);
		ft_free_dblechar_tab(tb);
		return (NULL);
	}
	ret = exec_op(tb);
	return (ret);
}
