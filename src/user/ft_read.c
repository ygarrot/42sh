/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:33:27 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/18 14:44:01 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static int		ft_sigintcall(t_line *line)
{
	ft_sigint_clear(line);
	return (-1);
}

static t_parser	*ft_getparser(t_line *line)
{
	int			i;
	t_parser	*tmp;

	if (!line)
		return (0);
	i = line->parser_nb;
	tmp = (line->parser);
	if (i < 1)
		return (0);
	i--;
	while (tmp && i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	return (tmp);
}

int				ft_read(t_line *line, int *val)
{
	char		buf[BUFFSIZE + 1];
	char		tmp[2 * BUFFSIZE + 1];
	int			re;

	ft_bzero((void*)tmp, 2 * BUFFSIZE);
	ft_sigint(0);
	while (1)
	{
		if (ft_sigint(0))
			return (ft_sigintcall(line));
		val[9] = read(STDIN_FILENO, buf, BUFFSIZE);
		if (ft_sigint(0) || val[9] < 0)
			return (ft_sigintcall(line));
		buf[val[9]] = 0;
		ft_strcat(tmp, buf);
		if ((re = ft_read_process(line, val, tmp, ft_getparser(line))))
			return (re);
	}
	return (0);
}

int				ft_read_process(t_line *line, int *val,
		char *tmp, t_parser *pars)
{
	int	i[3];
	int	re;

	ft_bzero((void*)i, sizeof(i));
	while (!i[0] || ft_strlen(tmp) - i[1] > BUFFSIZE)
	{
		if (tmp[i[1]] == 4 && (re = ft_read_eot(line, val, pars)))
			return (re);
		i[1] += (tmp[i[1]] == 4);
		if (tmp[i[1]] == '\n' &&
				(re = ft_read_newline(line, val, pars)))
			return (re);
		i[1] += (tmp[i[1]] == '\n');
		i[1] += ft_specialchar(line, &tmp[i[1]], val);
		if ((i[2] = ft_lentospecial(&tmp[i[1]])))
			ft_printnchar(line, &tmp[i[1]], val, i[2]);
		i[0] = 1;
		i[1] += i[2];
	}
	i[2] = -1;
	while (i[1] + ++i[2] < 2 * BUFFSIZE)
		tmp[i[2]] = tmp[i[1] + i[2]];
	tmp[i[2]] = 0;
	return (0);
}
