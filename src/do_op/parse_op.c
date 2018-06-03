/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:06:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/03 14:32:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#define OP_COMP "== != <= >= < >"
#define OP_ASSIGN "= *= /= %= += -= <<= >>= &= ^= |="

//#define OP_BIT "<< >> | || && & ^ ~"
#define ALL_OP "*= /= %= += -= <<= >>= &= ^= |=  == != <= >= -- ++ << >> || | ** && & ^ ~ < > = * / % - + "


# define COMP (char *[14]){ "==", "!=", "<=", ">=", "<", ">"}
# define ASSIGN (char *[14]){"*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=", "="}

	
#include "../../includes/sh.h"

int		is_local(char *str)
{
	if (1)
		return (1);
	else if (2)
		return (0);
}

int		parenth(char **str, int i)
{
	int tmp;

	tmp = i;
	if (!*str)
		return (1);
	while ((*str)[++i])
	{
		if ((*str)[i] == '(')
		{
			while ((*str)[++i])
			{
				if ((*str)[i] == ')' && ((tmp < 0 ? (*str)[i] = '\0' : 0) || 1))
				{
					return (i);
				}
				if ((*str)[i] == '(' && (i = parenth(str, i - 1)) < 0)
					return (-ft_printf("Parenthesis error\n"));
			}
			return (-1);
		}
	}
	return (i);
}

int	 parse_op(char *str)
{
	char	**op_tb;
	int			tab_len;
	int		res;

	ft_printf("{red}[%s]{reset}\n", str);
	char **all = ft_strsplit(ALL_OP, ' ');
	op_tb = ft_custom_split(str, all);
	tab_len = ft_tablen(op_tb) ;
	while (--tab_len + 1)
	{
		if (parenth(&op_tb[tab_len], -1) < 0 || (get_sep(op_tb[tab_len], all) >= 0
			&& ((tab_len <= 0 || get_sep(op_tb[tab_len - 1], all) >= 0)
			|| (!op_tb[tab_len + 1] || get_sep(op_tb[tab_len + 1], all) >= 0))))
			exit(ft_printf("2 operators\n"));
		if (get_sep(op_tb[tab_len], ASSIGN) >= 0 && ft_str_isdigit(op_tb[tab_len - 1]))
			exit(ft_printf("lvalue required"));
		if (ft_charchr('*', op_tb[tab_len]) >= 0
				|| ft_charchr('/',op_tb[tab_len]) >= 0)
		{
			if (ft_str_isdigit(op_tb[tab_len - 1]) && !ft_atoi(op_tb[tab_len - 1 ]))
				exit(ft_printf("Divide by 0\n"));
			else if (!ft_str_isdigit(op_tb[tab_len - 1]) && ft_atoi(0))
				exit(ft_printf("Divide by 0\n"));
		}
	}
	return (exec_op(op_tb));
}

int	main()
{
	ft_printf("%d\n", parse_op("(2+3)+4*2"));
}
