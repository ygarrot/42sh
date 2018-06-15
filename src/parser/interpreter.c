/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:27:49 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/10 15:24:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	add_comm(t_com *com, char *str)
{
	t_tb	*to_add;
	t_tb	*temp;

	if (!com || !str)
		return;
	mallcheck(to_add = (t_tb*)ft_memalloc(sizeof(t_tb)));
	to_add->str = str;
	if (!(temp = com->tb))
	{
		com->tb = to_add;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
}

void	add_redi(t_com *com, t_redi *toadd)
{
	if (!com->redi)
	{
		com->redi = toadd;
		return ;
	}
	while (com->redi->next)
		com->redi = com->redi->next;
	com->redi->next = toadd;
}

char	*get_redi(char *str, t_com *com)
{
	t_redi	*redi;
	int		ind;
	int		i[5];

	while ((ind = search_op(str, REDI)) >= 0)
	{
		mallcheck(redi = (t_redi*)ft_memalloc(sizeof(t_redi)));
		i[0] = ind -
			(ft_isdigit(str[ind - 1]) && ind > 1 && str[ind - 2] == ' ');
		redi->type = get_sep(&str[ind], REDI);
		redi->fd[0] = (i[0] == ind - 1) ? ft_atoi(&(str[i[0]]))
			: redi->type % 2;
		ind += ft_strlen(REDI[redi->type]);
		while (str[ind] && str[ind] == ' ')
			ind++;
		if ((i[1] = ft_strlento(&str[ind], ' ')))
			i[1] -= (str[ind + i[1] - 1] == ' ');
		redi->path = ft_strndup(&str[ind], i[1]);
		set_redi_path(redi);
		ft_strcpy(&str[i[0]], &str[ind + i[1]]);
		add_redi(com, redi);
	}
	return (str);
}

void	norm(t_shell *sh, t_parser *tmp, t_com *com)
{
	int		i;

	if (tmp->next)
		mallcheck(com->next = (t_com*)ft_memalloc(sizeof(t_com)));
	if (!tmp->comm)
		return ;
	(void)sh;
	get_redi(tmp->comm, com);
	mallcheck(com->cli = ft_strsplit_comm(tmp->comm, " "));
	i = -1;
	while (com->cli[++i])
	{
		if (com->cli[i] && *com->cli[i])
			add_comm(com, com->cli[i]);
	}
}

void	split_co(t_shell *sh, t_parser *tmp)
{
	t_com		*com;
	t_parser	*to_del;

	if (!tmp)
		return ;
	mallcheck(com = (t_com*)ft_memalloc(sizeof(t_com)));
	sh->com = com;
	while (tmp)
	{
		norm(sh, tmp, com);
		com->type = tmp->type;
		to_del = tmp;
		tmp = tmp->next;
		com = com->next;
		ft_memdel((void**)&to_del->comm);
		ft_memdel((void**)&to_del);
	}
	sh->begin = sh->com;
	sort_comm(sh);
}
