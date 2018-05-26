/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 11:28:55 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/18 12:24:45 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_direction_del(void *content, size_t t)
{
	if (t == sizeof(t_direction))
		ft_strdel(&(((t_direction*)content)->out_file));
	free(content);
}

void	ft_command_del(void *com, size_t t)
{
	if (t == sizeof(t_command))
	{
		ft_lstdel(&(((t_command*)com)->direction), ft_direction_del);
		ft_strdel(&(((t_command*)com)->line));
	}
	free(com);
}

int		ft_realloc_line(t_line *line, int *val, int newsize)
{
	char	*s;
	int		tmp;
	char	*str;

	s = (val[4] ? line->line : line->eof);
	if (!s || !(str = (char*)ft_memalloc(newsize)))
		return (-1);
	tmp = (val[4] ? line->size_line : line->size_eof);
	while (tmp-- > 0)
		str[tmp] = s[tmp];
	ft_strdel(&s);
	if (val[4])
	{
		line->size_line = newsize;
		line->line = str;
	}
	else
	{
		line->size_eof = newsize;
		line->eof = str;
	}
	return (1);
}

void	ft_delline(t_line *line)
{
	t_parser	*tmp;

	if (!line)
		return ;
	ft_strdel(&(line->line));
	ft_strdel(&(line->eof));
	while (line->parser)
	{
		tmp = line->parser;
		line->parser = tmp->next;
		ft_strdel(&(tmp->comm));
		ft_memdel((void**)&tmp);
	}
}

void	ft_delparser(t_parser **pars)
{
	t_parser	*el;
	t_parser	*tmp;

	if (!pars || !*pars)
		return ;
	el = *pars;
	while (el)
	{
		tmp = el;
		el = el->next;
		ft_strdel(&(tmp->comm));
		free(tmp);
		tmp = 0;
	}
}
