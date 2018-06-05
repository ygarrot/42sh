/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 09:52:26 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/27 14:58:48 by tcharrie         ###   ########.fr       */
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
	if ((!tgetstr("im", NULL) || !tgetstr("ei", NULL)) && !tgetstr("ic",
				NULL))
		write(2, NO_CHAR_MSG, ft_strlen(NO_CHAR_MSG));
	if (!(tgetstr("al", NULL)))
		write(2, NO_NEWLINE_MSG, ft_strlen(NO_NEWLINE_MSG));
	if (!(tgetstr("dl", NULL)))
		write(2, NO_DELLINE_MSG, ft_strlen(NO_DELLINE_MSG));
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
	if (tcsetattr(STDIN_FILENO, 0, &term) == -1)
		ft_fatal("Can't set the terminal to have great power, exit ...");
	return (1);
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
