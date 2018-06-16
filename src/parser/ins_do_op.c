/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_do_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:59:58 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 11:35:03 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void sub_ar(t_shell *sh, char **arg, int i)
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
	*todel = ft_strndup(*arg, i - 2 );
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

	if (!ft_strncmp(str, "((", 2))
	{
		todel = parse_op(str);
		ft_memdel((void**)&todel);
		return ;
	}
	if (!bracket(++str, "()"))
		return ;
	str[ft_strlen(str) - 1] = '\0';
	tmp.line = ft_strdup(str);
	ft_subshell_set(ft_subshell_get() + 1);
	sh->env = *ft_storeenv(0, ft_subshell_get());
	sh->sub.is_sub = 2;
	hard_split(sh, &tmp);
	ft_subshell_set(ft_subshell_get() - 1);
	sh->env = *ft_storeenv(0, ft_subshell_get());
}

void	replace_local(t_shell *sh, char **str, int i)
{
	if (i > 0 || !str || !*str)
		return ;
	if (**str == '(')
		sub_shell(sh, *str);
	else if (ft_strlento_comm(*str, "="))
	{
		if (!str[1])
			ft_variable_builtin(*str);
	}
	else
		return ;
	ft_memdel((void**)&(*str));
}
