/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:02:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:36:56 by ygarrot          ###   ########.fr       */
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
		ft_printf("ici\n");
		line = ft_getentry();
		ft_printf("la\n");
		while (line.line == 0)
		{
			ft_delline(&line);
			line = ft_getentry();
		}
		if (ft_terminal_reset(0) == -1)
			ft_fatal("Failed to reset terminal setting");
		hard_split(&sh, &line);
		if (ft_terminal_set(0) == -1)
			ft_fatal("Failed to set terminal settings back");
		ft_delline(&line);
	}
	erase_shell(&sh);
}
