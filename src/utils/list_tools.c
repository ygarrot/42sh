/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:26:45 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/02 11:14:56 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

t_parser	*push_front(t_parser *com, char *str, int type)
{
	t_parser	*ret;
	t_parser	*begin;
	char		*trim;

	begin = com;
	if (!str)
		return (NULL);
	trim = ft_strtrim(str);
	ft_memdel((void**)&str);
	if (com && !com->comm)
	{
		com->comm = trim;
		com->type = type;
		return (com);
	}
	mallcheck(ret = (t_parser*)ft_memalloc(sizeof(t_parser)));
	ret->comm = trim;
	ret->type = type;
	if (!com)
		return (ret);
	while (com->next)
		com = com->next;
	com->next = ret;
	return (begin);
}

void		shift_com(t_shell *sh, int fail)
{
	if (!sh->com)
		return ;
	sh->com = sh->com->next;
	sh->com && !(sh->com->type & 4) ? replace_in(sh, sh->com) : 0;
	while (sh->com && (!sh->com->cli 
	|| (sh->com->type && !(sh->com->type & (fail >= 0 ? 2 : 1)))))
	{
		!(sh->com->type & 4) ? replace_in(sh, sh->com) : 0;
		sh->com = sh->com->next;
		if (sh->com->type & 32)
			return ;
	}
}

void		free_comm(t_shell *sh)
{
	t_com *to_del;

	if (!sh->begin)
		return ;
	while (sh->begin)
	{
		to_del = sh->begin;
		epur_tb(to_del, to_del->len);
		sh->begin = sh->begin->next;
		ft_free_dblechar_tab(to_del->cli);
		ft_memdel((void**)&to_del);
	}
}

void		free_parser(t_parser *begin)
{
	t_parser *to_del;

	while (begin)
	{
		to_del = begin;
		begin = begin->next;
		ft_memdel((void**)&to_del->comm);
		ft_memdel((void**)&to_del);
	}
}

void		free_globs(t_glob *glob)
{
	t_paths		*to_del;

	if (!glob)
		return ;
	while (glob->paths)
	{
		to_del = glob->paths;
		glob->paths = glob->paths->next;
		ft_memdel((void**)&to_del->name);
		ft_memdel((void**)&to_del);
	}
	ft_memdel((void**)&glob);
}
