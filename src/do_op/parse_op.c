/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:06:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 18:11:19 by ygarrot          ###   ########.fr       */
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

int	check_ternaries(char **tb)
{
	int	i;
	
	i = 0;
	if (get_sep(tb[i++], all_op(0)) >= 0)
		return (i + 1);
	if (*tb[i++ + 1] == '?')
		if (!(i = check_ternaries(&tb[i + 1])))
			return (-1);
	if (*tb[i++] != ':' || !tb[i] || get_sep(tb[i++], all_op(0)) >= 0 )
		return (-1);
	return (i);
}


int	check_all(char **tb)
{
	int		i;
	char		**all;

	i = -1;
	all = all_op(0);
	while (tb[++i])
	{
		if (parenth(&tb[i], -1, 'a', 0) < 0)
			return (0);
		if (get_sep(tb[i], CREMENT) < 0 && get_sep(tb[i], all) >= 0
			&& ((i <= 0 || get_sep(tb[i - 1], all) >= 0)
			|| (!tb[i + 1] || get_sep(tb[i + 1], all) >= 0)))
			return (0 & ft_printf("2 operators\n"));
		if (get_sep(tb[i], all_op(1)) >= 0
				&& tb[i][0] != '=' && ((i - 1) < 0 || ft_str_isdigit(tb[i - 1])))
			return (0 & ft_printf("lvalue required\n"));
	}
	return (1);
}


char	*parse_op(char *str)
{
	char	**tb;
	int			i;

	str[ft_strlen(str) - 1] = '\0';
	ft_strcpy(str, &str[1]);
	tb = ft_custom_split(str, all_op(0), 0);
	if (!tb || !check_all(tb))
		return (NULL);
	i = -1;
	while (++i)
	{
		//ft_printf("%s\n", tb[i]);
		if (*tb[i] != '(' && ft_mcharchr("/%", tb[i]) >= 0)
		{
			if ((ft_str_isdigit(tb[i + 1])
	&& !ft_atoi(tb[i + 1])) || (!ft_str_isdigit(tb[i - 1])
	&& ft_atoi(0)))
			{
				ft_printf("Divide by 0\n") ;
				return (NULL);
			}
		}
	}
	return (exec_op(tb));
}
