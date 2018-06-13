/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 15:44:24 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_read_recover_execute(t_line *line, int *val, char *buff)
{


}

static void	ft_read_recover_pars(t_line *line, int *val, char *buff, t_read p)
{
	int	len;

	if (!line || !val || !buff || !*buff || !line->line)
		return ;
	len = parser.readline_active ? ft_lentospecial(buff) : (int)ft_strlen(buff);
	if (p.readline_active && 0 >= len)
		ft_read_recover_execute(line, val, buff);
	else if (p.readline_active)
		;
	else
	{
		line->eof = (char*)ft_malloc(ft_strlen(line->line) + len + 1)
		line->eof[0] = 0;
		ft_strcat(line->eof, line->line);
		ft_strcat(line->eof, buff);
		*buff = 0;
		ft_strdel(&line->line);
		line->line = line->eof;
	}
}

int			ft_read_recover_end(char *str, t_read p)
{
	size_t	size;

	size = ft_strlen(str);
	if (ft_read_timer_sig_interrup(0) == 1)
		return (1);
	if (p.nchars_exact > 0 && size > p.nchars_exact)
		ft_addtofd(&str[size + 1], p.fd);
	if (p.nchars_exact > 0)
		return (size >= p.nchars_exact);
	if (p.nchars > 0 && size > p.nchars)
		ft_addtofd(&str[size + 1], p.fd);
	if (p.nchars > 0 && size >= p.nchars)
		return (1);
	if (size == 0)
		return (0);
	size = 0;
	while (str[size])
	{
		if (ft_strprefix(p.delim, &str[size]))
			return (1);
		size++;
	}
	return (0);
}

char		*ft_read_recover(t_read *parser)
{
	t_line	line;
	int		val[14];
	char	buff[BUFFSIZE + 1];
	char	tmp[2 * BUFFSIZE + 1];

	if (!parser)
		return (0);
	line.line = (char*)ft_memalloc(1);
	ft_bzero((void*)val, sizeof(val));
	ft_bzero((void*)buff, sizeof(buff));
	ft_bzero((void*)tmp, sizeof(buff));
	val[4] = 1;
	while (line.line && !ft_read_recover_end(line.line, *p))
	{
		val[9] = read(parser->fd, buff, BUFFSIZE);
		if (val[9] < 0)
			ft_strdel(&line.line);
		if (val[9] < 0)
			return (0);
		buff[val[9]] = 0;
		ft_strcat(tmp, buff);
		ft_read_recover_pars(&line, val, tmp, *parser);
	}
	return (str);
}
