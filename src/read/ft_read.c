/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:37:21 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 12:01:49 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_builtin(char **arg, char ***env)
{
	t_read	parser;
	char	*str;

	if (!arg || !env || !*arg || !*env)
		return ;
	parser = ft_read_parser(arg);
	if (parser.error)
		;
	else if (ft_read_timer(&parser) == -1)
		;
	else if (ft_read_initterminal(&parser) == -1)
		;
	else
	{
		ft_fd_set(parser.fd);
		str = ft_read_recover(&parser);
		if (ft_read_assign(&parser, str) == -1)
			parser.error = 1;
		ft_read_terminal_reset(0, parser.fd);
		ft_strdel(&str);
	}
	ft_strdel(&parser.delim);
	ft_free_dblechar_tab(parser.variables);
	ft_fd_set(STDIN_FILENO);
}

char	*ft_read_delim(void)
{
	t_variable	*var;

	if ((var = ft_variableget("IFS")))
	{
		if (var->deep == 1 && var->str)
			return (var->str);
	}
	return (" \n");
}
