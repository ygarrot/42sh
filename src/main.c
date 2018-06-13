/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:02:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/13 13:00:48 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main(int ac, char **av, char **env)
{
	t_shell sh;
	t_line	line;

	(void)ac;
	(void)av;
	f_point(&sh, av);
	ft_initialisation(env, &sh);
	alias_file(&sh);
	while (1)
	{
		line = ft_getentry();
		while (line.line == 0)
		{
			line = ft_getentry();
			ft_delline(&line);
		}
		hard_split(&sh, &line);
		ft_delline(&line);
	}
	erase_shell(&sh);
}
