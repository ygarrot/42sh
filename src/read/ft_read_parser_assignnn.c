/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parser_assignnn.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:27 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 15:45:38 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_read_parser_u(t_read *parser, char *str)
{
	int	i;

	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (-1);
	parser->fd = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && parser->fd <= FD_SETSIZE / 10)
		parser->fd = (parser->fd * 10) + (str[i++] - '0');
	if (str[i] || fcntl(parser->fd, F_GETFD))
	{
		ft_putstr_fd("21sh: read: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": invalid file descriptor specification\n",
					STDERR_FILENO);
		parser->error = 1;
		return (-1);
	}
	parser->fd = STDIN_FILENO;
	return (2);
}

static int	ft_read_parser_t_error(char *str)
{
	ft_putstr_fd("21sh: read: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": invalid timeout specification\n", STDERR_FILENO);
	return (-1);
}

int			ft_read_parser_t(t_read *parser, char *str)
{
	int	tmp;
	int	i;

	if (!str)
		return (ft_read_usage(parser));
	if (!parser || (tmp = 0))
		return (2);
	parser->timer.tv_sec = 0;
	while (str[tmp] >= '0' && str[tmp] <= '9' && parser->timer.tv_sec >= 0)
		parser->timer.tv_sec = (parser->timer.tv_sec * 10) + (str[tmp++] - '0');
	parser->error = (str[tmp] >= '0' && str[tmp] <= '9');
	tmp += (str[tmp] == '.' ? 1 : 0);
	i = 0;
	while (str[tmp] >= '0' && str[tmp] <= '9' && parser->timer.tv_nsec >= 0)
		if (tmp++ > 0 && i++ <= 8)
			parser->timer.tv_nsec =
					(parser->timer.tv_nsec * 10) + (str[tmp - 1] - '0');
	parser->timer.tv_nsec =
			parser->timer.tv_nsec * ft_power(10, i <= 8 ? 8 - i : 0);
	if (parser->timer.tv_nsec == 0 && parser->timer.tv_nsec == 0)
		parser->timer.tv_nsec = 1;
	parser->error = (parser->error || str[tmp]);
	if (parser->error)
		return (ft_read_parser_t_error(str));
	return (2);
}
