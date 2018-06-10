/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:06:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 12:54:41 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OP_ASSIGN "= *= /= %= += -= <<= >>= &= ^= |="

#define ALL_OP "*= /= %= += -= <<= >>= &= ^= |=  == != <= >= -- ++ << >> || | ** && & ^ ~ < > = * / % - + ? :"

# define ASSIGN (char *[14]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=", "="}

#include "../../includes/sh.h"

int		parenth(char **str, int i, char rep, bool recc)
{
	if (!*str)
		return (1);
	while ((*str)[++i])
	{
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
	}
	return (i);
}

int	check_ternaries(char **tb)
{
	int	i;
	
	i = 0;
	if (get_sep(tb[i++], all) >= 0)
		return (i + 1);
	if (tb[i++ + 1] == '?')
		if (!check_ternaries(tb[i + 1]))
			return (-1);
		
	if (tb[i++] != ':' || !tb[i] || get_sep(tb[i++], all) >= 0 )
		return (-1)
	return (i);
}

char	*parse_op(char *str)
{
	char	**op_tb;
	int			tab_len;

	str[ft_strlen(str) - 1] = '\0';
	ft_strcpy(str, &str[1]);
	char **all = ft_strsplit(ALL_OP, ' ');
	op_tb = ft_custom_split(str, all, 0);
	tab_len = ft_tablen(op_tb) ;
	while (--tab_len + 1)
	{
		if (parenth(&op_tb[tab_len], -1, 'a', 0) < 0 || (get_sep(op_tb[tab_len], all) >= 0
			&& ((tab_len <= 0 || get_sep(op_tb[tab_len - 1], all) >= 0)
			|| (!op_tb[tab_len + 1] || get_sep(op_tb[tab_len + 1], all) >= 0))))
			exit(ft_printf("2 operators\n"));
		if (get_sep(op_tb[tab_len], ASSIGN) >= 0 && op_tb[tab_len][0] != '=' && ft_str_isdigit(op_tb[tab_len - 1]))
			exit(ft_printf("lvalue required\n"));
		//ft_printf("%s\n", op_tb[tab_len]);
		if (*op_tb[tab_len] != '(' && ft_mcharchr("/%", op_tb[tab_len]) >= 0)
		{
			if ((ft_str_isdigit(op_tb[tab_len + 1])
	&& !ft_atoi(op_tb[tab_len + 1])) || (!ft_str_isdigit(op_tb[tab_len - 1])
	&& ft_atoi(0)))
			{
				ft_printf("Divide by 0\n") ;
				return (NULL);
			}
		}
	}
	return (exec_op(op_tb));
}
