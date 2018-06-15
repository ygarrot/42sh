/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 14:16:55 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_recover_pars(t_line *line, int *val, char *buff, t_read *p)
{
	int	len;
	int	i;

	if (!p || !line || !val || !buff || !*buff || !line->line)
		return ;
	len = parser->readline_active ? ft_lentospecial(buff) : (int)ft_strlen(buff);
	if (p->readline_active && 0 == len)
	{
		len = ft_read_recover_execute(line, val, buff, p->echo);
		if (ft_strprefix(NEWLINE, buff) && p->echo)
			write(p->fd, "\n", 1);
	}
	else if (p->readline_active && p->echo)
		ft_printnchar(line, buff, val, len);
	else
		ft_read_recover_insert(line, val, buff, len);
	i = 0;
	while (buff[len])
		buff[i++] = buff[len++];
	buff[i] = 0;
}

int		ft_read_recover_end(char *str, t_read p)
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

int		ft_read_recover_init(t_read *parser, int *val, size_t size,
		t_line *line)
{
	if (!parser)
		return (-1);
	ft_bzero((void*)val, size);
	if (!(line->line = (char*)ft_memalloc(ft_strlen(parser->readline) +
					ft_strlen(parser->prompt) + 1)))
		return (-1);
	line->line = 0;
	if (parser->prompt)
		ft_strcat(line->line, parser->prompt);
	if (parser->readline)
		ft_strcat(line->line, parser->readline);
	val[1] = ft_strlen(parser->prompt);
	val[5] = val[1];
	val[0] = val[1] + ft_strlen(parser->readline);
	val[4] = 1;
	return (0);
}

char	*ft_read_recover(t_read *parser)
{
	t_line	line;
	int		val[14];
	char	buff[BUFFSIZE + 1];
	char	tmp[2 * BUFFSIZE + 1];

	if (ft_read_recover_init(parser, val, sizeof(val), &line) == -1)
		return (0);
	ft_bzero((void*)buff, sizeof(buff));
	ft_bzero((void*)tmp, sizeof(tmp));
	while (line.line && !ft_read_recover_end(line.line, *p))
	{
		val[9] = read(parser->fd, buff, BUFFSIZE);
		if (val[9] < 0)
			ft_strdel(&line.line);
		if (val[9] < 0)
			return (0);
		buff[val[9]] = 0;
		ft_strcat(tmp, buff);
		ft_read_recover_pars(&line, val, tmp, parser);
	}
	return (str);
}
