/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:06:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/02 17:35:52 by ygarrot          ###   ########.fr       */
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

int		parenth(char **str)
{
	int i;
	int	ind;

	i = -1;
	if (!*str)
		return (1);
	while (&(*str)[++i])
	{
		if ((*str)[i] == '(')
		{
			if ((ind = ft_charchr(')', &(*str)[i])) >= 0)
			{
				if ((*str)[i + ind + 1])
					return (0);
				(*str)[i + ind] = '\0';
			}
			else
				return (0);
		}
		else if ((*str)[i] != ' ')
			return (1);
	}
	return (1);
}

int	 parse_op(char *str)
{
	char	**op_tb;
	int			tab_len;
	int		res;

	char **all = ft_strsplit(ALL_OP, ' ');
	op_tb = ft_custom_split(str, all);
	tab_len = ft_tablen(op_tb);
	while (--tab_len)
	{
		if (!parenth(&op_tb[tab_len]) || (get_sep(op_tb[tab_len], all) >= 0
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
	ft_printf("%d\n", parse_op("2*2 +2 +(2*4)"));
}
