/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_do_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:59:58 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 16:02:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	sub_ar(t_shell *sh, char **arg, int i)
{
	char *todel[3];

	if ((*arg)[i++] != '$' || (*arg)[i++] != '(')
		return ;
	if (parenth(arg, i - 2, (*arg)[i] == '(' ? '\0' : '`', 0) < 0)
		return ;
	todel[2] = *arg;
	if ((*arg)[i] != '(')
	{
		(*arg)[i - 2] = '`';
		(*arg)[i - 1] = ' ';
		comm_substitute(sh, arg, i);
		return ;
	}
	*todel = ft_strndup(*arg, i - 2);
	!*todel ? *todel = ft_strnew(1) : 0;
	if (!(todel[1] = parse_op(&(*arg)[i])))
		todel[1] = ft_strnew(1);
	mallcheck(*arg = ft_implode(todel[1], *todel, &(*arg)[ft_strlen(*arg)]));
	ft_memdel((void**)&(*todel));
	ft_memdel((void**)&todel[1]);
	ft_memdel((void**)&todel[2]);
}

void	sub_shell(t_shell *sh, char *str)
{
	char	*todel;
	t_line	tmp;

	if (!ft_strncmp(str, "((", 2) && str[ft_strlen(str) - 2] == ')')
	{
		todel = parse_op(str);
		ft_memdel((void**)&todel);
		return ;
	}
	if (!bracket(str, "()") ||  parenth(&str,-1, '\0', 0) < 0)
		return ;
	++str;
	tmp.line = str;
	tmp_sh(sh, 1, 0);
	ft_subshell_set(ft_subshell_get() + 1);
	sh->env = *ft_storeenv(0, ft_subshell_get());
	hard_split(sh, &tmp);
	ft_subshell_set(ft_subshell_get() - 1);
	sh->env = *ft_storeenv(0, ft_subshell_get());
	tmp_sh(sh, 0, 0);
}

void	replace_local(t_shell *sh, char **str, int i, int ret)
{
	if (i > 0 || !str || !*str)
		return ;
	if (**str == '(')
		sub_shell(sh, *str);
	else if (ft_strlento_comm(*str, "="))
	{
		if (!ret)
			ft_variable_builtin(*str);
	}
	else
		return ;
	ft_memdel((void**)&(*str));
}

void	tmp_sh(t_shell *sh, int index, int is_sub)
{
	static t_com *co;
	static t_com *begin;

	if (index == 1)
	{
		begin = sh->begin;
		co = sh->com;
		sh->com = 0;
		sh->begin = 0;
		sh->sub.is_sub = is_sub;
	}
	else
	{
		begin = sh->begin;
		sh->com = co;
		sh->begin = begin;
		sh->sub.is_sub = 0;
	}
}
