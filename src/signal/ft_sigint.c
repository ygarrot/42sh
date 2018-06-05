/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:45:56 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/26 16:26:28 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_sigint(int sig)
{
	static int	status = 0;
	int			tmp;

	if (sig == SIGINT)
		ft_addtofd("\v", STDIN_FILENO);
	tmp = status;
	status = (sig == SIGINT);
	return (tmp);
}

int		ft_sigint_clear(t_line *line)
{
	ft_strdel(&(line->line));
	ft_strdel(&(line->eof));
	tputs(tgetstr("cd", 0), 0, writechar);
	ft_printf("{whiteblack}\n");
	return (SIGINT);
}
