/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:14:26 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:29:26 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	init_point(t_shell *sh)
{
	if ((sh->std[0] = dup(STDIN_FILENO)) < 0
			|| (sh->std[1] = dup(STDOUT_FILENO)) < 0
			|| (sh->std[2] = dup(STDERR_FILENO)) < 0)
	{
		ft_putendl_fd("std dup error", 2);
		ft_exit(sh, EXIT_FAILURE);
	}
	sh->built[0] = &ft_cd;
	sh->built[1] = &ft_setenv;
	sh->built[2] = &ft_unsetenv;
	sh->built[3] = &ft_alias;
	sh->built[4] = &ft_unalias;
	sh->built[5] = &ft_read_builtin;
	sh->built[6] = &ft_unset;
	sh->built[7] = &ft_export;
	sh->f_built[0] = &ft_echo;
}

void	f_point(t_shell *sh, char **argv)
{
	ft_bzero(sh, sizeof(sh));
	if ((!argv[1] || ft_strcmp(argv[1], "-h")) &&
			!(sh->hash_tb = (t_btree**)ft_memalloc(1000 * sizeof(t_btree*))))
		exit(EXIT_FAILURE);
	ft_printf("ici\n");
	sh->tb_built = (char *[11]){"cd", "setenv", "unsetenv", "alias", "unalias",
		"read", "unset", "export", 0};
	ft_printf("la\n");
	sh->tb_built = ft_strtbdup(sh->tb_built);
	init_point(sh);
}
