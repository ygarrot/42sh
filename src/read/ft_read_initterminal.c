/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_initterminal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 12:47:14 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	ft_read_initterminal(t_read *parser)
{
	t_termios	term;

	if (!parser)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		ft_putstr_fd("21sh: read: Failed to recover terminal data\n",
				STDERR_FILENO);
		parser->error = 1;
		return (-1);
	}
	ft_read_terminal_reset(&term, parser->fd);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;
	if (tcsetattr(parser->fd, 0, &term) == -1)
	{
		ft_putstr_fd("21sh: read: Failed to set an active terminal\n",
				STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	ft_read_terminal_reset(t_termios *term, int fd)
{
	static t_termios	save;

	if (fd < 0)
		return (-1);
	if (term)
		save = *term;
	else
		return (tcsetattr(STDIN_FILENO, 0, &save));
	return (0);
}
