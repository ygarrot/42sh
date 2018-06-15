/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:06:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 18:24:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

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

char	**all_op(int index)
{
	static char **tb = 0;
	static char **assign = 0;
	if (!tb)
	{
		tb = ( char *[40]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=" "&=", "^=",
	"|=", "==", "!=", "<=", ">=", "--", "++", "<<", ">>", "||", "|", "**", 
	"&&", "&", "^", "~", "<", ">", "=", "*", "/", "%", "-", "+", "?", ":", 0};
		tb = ft_strtbdup(tb);
	}
	if (!assign)
	{
		assign = (char *[20]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=",
		"^=", "|=", "=", 0};
		assign = ft_strtbdup(assign);
	}
	return (!index ? tb : assign);
}

int	check_classic(char **tb, int *i)
{
	int		is_op;

	if (tb[*i] && ft_isin(*tb[*i], "-~+") && !tb[*i][1] && ++*i)
		return (check_classic(tb, i));
	if (!tb[*i] || (!(is_op = check_op(tb[*i])) && !tb[++*i]))
		return (1);
	if (!(is_op = check_op(tb[*i])))
		return (0 & ft_printf("operator expected\n"));
	else if (is_op)
	{
		if (get_sep(tb[*i], all_op(1)) >= 0
			&& tb[*i][0] != '=' && ((i - 1) < 0 || ft_str_isdigit(tb[*i - 1])))
			return(0 & ft_printf("lvalue required\n"));
		if (ft_isin(*tb[*i], ":?") && (--*i || 1))
			return (1);
		if (get_sep(tb[*i], CREMENT) >= 0 && ++*i)
			return (check_classic(tb, i));
		else if (!check_op(tb[++*i]) && !check_op(tb[*i]))
			return (check_classic(tb, i));
		return (0 & ft_printf("unknown error\n"));
	}
	return (is_op && get_sep(tb[++*i], CREMENT) >= 0 ?
	check_classic(tb, i) : 0 & ft_printf("no operator\n"));
}

int	check_op(char *str)
{
	if (!str)
		return (-1);
	if (get_sep(str, all_op(0)) >= 0)
		return (1);
	return (0);
}

#define TERN "ERREUR DE TERN SYNTAX"

int	check_ternaries(char **tb, int *i)
{
	if (check_op(tb[*i]))
		return (1);
	if (!tb[++*i] || *tb[*i] != '?' || check_op(tb[++*i]) || !tb[*i + 1])
		return (0 & ft_printf(TERN));
	if (*tb[*i + 1] == '?')
		if (!(check_ternaries(&tb[*i], i)))
			return (0 & ft_printf("%s\n", TERN, "1"));
	if (!check_classic(tb, i))
		return (0 & ft_printf("%s\n", TERN, "2"));
	if (!tb[*i] || *tb[++*i] != ':')
		return (0 & ft_printf("%s\n", TERN, "3"));
	++*i;
	return (tb[*i] ? check_classic(tb, i) : 0 & ft_printf("%s %s\n", TERN, "3"));
}

int	check_all(char **tb)
{
	int		i;
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
		return (NULL);
	ret = exec_op(tb);
	return (ret);
}
