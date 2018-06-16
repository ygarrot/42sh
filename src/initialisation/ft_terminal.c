/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 09:52:26 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 12:01:59 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_init_terminal_data(void)
{
	char	*termtype;
	int		success;
	char	term_buffer[2048];

	if (!(termtype = getenv("TERM")))
		ft_fatal("No terminal type is defined in the environment");
	success = tgetent(term_buffer, termtype);
	if (success < 0)
		ft_fatal("Could not access the termcap data base");
	else if (success == 0)
		ft_fatal("The terminal type is not defined");
	if (tgetnum("li") == ERR || tgetnum("co") == ERR)
		ft_fatal("Can't get terminal size");
}

int		ft_setattr(void)
{
	t_termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		ft_fatal("Can't recover the terminal structure");
	ft_terminal_reset(&term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;
	if (ft_terminal_set(&term) == -1)
		ft_fatal("Can't set the terminal to have great power, exit ...");
	return (1);
}

int		ft_terminal_set(t_termios *term)
{
	static t_termios	save;

	if (term)
		save = *term;
	return (tcsetattr(STDIN_FILENO, 0, &save));
}

int		ft_terminal_reset(t_termios *term)
{
	static t_termios	save;

	if (term)
		save = *term;
	else
		return (tcsetattr(STDIN_FILENO, 0, &save));
	return (1);
}
