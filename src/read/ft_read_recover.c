/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 12:44:58 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_recover_pars(t_line *line, int *val, char *buff, t_read *p)
{
	int	len;
	int	i;

	if (!p || !line || !val || !buff || !*buff || !line->line)
		return ;
	len = p->readline_active ? ft_lentospecial(buff) : (int)ft_strlen(buff);
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
	while (line.line && !ft_read_recover_end(&(line.line), *parser))
	{
		val[9] = read(parser->fd, buff, BUFFSIZE);
		if (val[9] < 0)
			ft_strdel(&line.line);
		if (!line.line || ft_read_recover_sig(&(line.line), *parser))
			return (line.line);
		buff[val[9]] = 0;
		ft_strcat(tmp, buff);
		ft_read_recover_pars(&line, val, tmp, parser);
	}
	parser->error = (parser->error || (val[12] != 2 && !line.line));
	return (line.line);
}
