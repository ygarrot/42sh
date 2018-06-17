/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:37:21 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/06 12:37:23 by tcharrie         ###   ########.fr       */
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
		return ;
	if (ft_read_timer(&parser) == -1)
		return ;
	if (ft_read_initterminal(&parser) == -1)
		return ;
	str = ft_read_recover(&parser);
	if (ft_read_assign(&parser, str) == -1)
		parser.error = 1;
	ft_read_resetterminal();
}
