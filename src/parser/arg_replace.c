/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:41:24 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:53:34 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	assign(char **arg, int i)
{
	char	*temp[3];
	char	*todel;
	int		len;

	if ((*arg)[i] == '$'
			|| ((*arg)[i] == '~' && (!i || (*arg)[i - 1] == ' ')))
	{
		temp[0] = (*arg)[i] == '$' ? &(*arg)[i + 1] : "HOME";
		len = ft_variable_toskip(temp[0]);
		len = len >= 0 ? (size_t)len : ft_strlen(temp[0]);
		todel = ft_strndup(temp[0], len);
		if (!local_env(&temp[1], todel))
			return ;
		todel = (i > 0 ? ft_strndup(*arg, i) : ft_strdup(""));
		temp[2] = *arg;
		*arg = ft_implode(temp[1], todel
				, &(*arg)[i + 1 + ((*arg)[i] == '$' ? len : 0)]);
		ft_memdel((void**)&temp[2]);
		ft_memdel((void**)&todel);
		ft_memdel((void**)&temp[1]);
	}
}

void	arg_replace(t_shell *sh, char **arg)
{
	int		i;

	i = -1;
	if (!arg || !*arg)
		return ;
	while ((*arg)[++i])
	{
		i += skip_double(&(*arg)[i]);
		sub_ar(sh, arg, i);
		comm_substitute(sh, arg, i);
		assign(arg, i);
		if (!arg[0] || !arg[0][i])
			return ;
	}
}

char	*replace_loop(t_shell *sh)
{
	t_list	*to_del;
	char	*glue;

	mallcheck(glue = ft_memalloc(sh->sub.size * sizeof(char) + 1));
	while (sh->sub.begin)
	{
		if (sh->sub.begin->content)
		{
			ft_strcat(glue, (char*)sh->sub.begin->content);
			sh->sub.begin->next ? ft_strcat(glue, " ") : 0;
		}
		to_del = sh->sub.begin;
		sh->sub.begin = sh->sub.begin->next;
		ft_memdel((void**)&to_del->content);
		ft_memdel((void**)&to_del);
	}
	return (glue);
}

void	comm_substitute(t_shell *sh, char **str, int i)
{
	t_line	tmp;
	t_shell	sub;
	char	*glue;
	int		len;
	char	*to_del[2];

	if ((*str)[i++] != '`' || ft_charchr('`', &(*str)[i]) <= 0)
		return ;
	ft_bzero(&sh->sub, sizeof(sh->sub));
	tmp_sh(&sub, sh, 1, 1);
	len = ft_strlento(&(*str)[i], '`');
	mallcheck(tmp.line = ft_strndup(&(*str)[i], len));
	hard_split(&sub, &tmp);
	if (!(*to_del = ft_strndup(*str, i - 1)))
		mallcheck(*to_del = ft_strnew(0));
	glue = replace_loop(&sub);
	to_del[1] = *str;
	mallcheck(*str = ft_implode(glue, *to_del, &(*str)[i + len + 1]));
	ft_memdel((void**)&glue);
	ft_memdel((void**)&tmp.line);
	ft_memdel((void**)&to_del[1]);
	ft_memdel((void**)&(*to_del));
	tmp_sh(&sub, sh, 0, 0);
}

void	get_sub(t_shell *sh)
{
	t_list *begin;

	while (wait(0) != -1)
		;
	if (!sh->sub.begin)
		mallcheck(sh->sub.begin = (t_list*)ft_memalloc(sizeof(t_list)));
	close(sh->sub.pipe[1]);
	if (dup2(sh->sub.pipe[0], STDIN_FILENO) == -1)
		ft_error("dup error", 0);
	begin = sh->sub.begin;
	while (begin->next)
		begin = begin->next;
	while (get_next_line(sh->sub.pipe[0], (char**)&begin->content) > 0)
	{
		sh->sub.size += ft_strlen((char*)begin->content) + 1;
		mallcheck(begin->next = (t_list*)ft_memalloc(sizeof(t_list)));
		begin = begin->next;
	}
	safe_dup(-1, 0, sh->sub.pipe);
	if (dup2(sh->std[0], STDIN_FILENO) == -1
		|| dup2(sh->std[1], STDOUT_FILENO) == -1)
	{
		ft_error("STD dup error", 0);
		ft_exit(sh, EXIT_FAILURE);
	}
}
