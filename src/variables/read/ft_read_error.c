/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:37:43 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/06 12:37:44 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	ft_read_usage(t_read *parser)
{
	if (parser)
		parser->error = 1;
	ft_putstr_fd("read : usage read [-ers] [-a array] [-d delim] [-i text] \
	[-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]\n", 2);
	return (-1);
}

int	ft_read_timeerror(char *str, t_read *parser)
{
	ft_putstr_fd("21sh: read: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid timeout specification", 2);
	if (parser)
		parser->error = 1;
	return (-1);
}
