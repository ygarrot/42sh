/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:14:26 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/27 15:42:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		f_point(t_shell *sh, char **argv)
{
	ft_bzero(sh, sizeof(sh));
	if ((!argv || ft_strcmp(*argv, "-h")) &&
		!(sh->hash_tb = (t_btree**)ft_memalloc(1000 * sizeof(t_btree*))))
		exit(EXIT_FAILURE);
	if ((sh->std[0] = dup(STDIN_FILENO)) < 0
		|| (sh->std[1] = dup(STDOUT_FILENO)) < 0
		|| (sh->std[2] = dup(STDERR_FILENO)) < 0)
	{
		ft_printf("std dup error\n");
		ft_exit(sh);
	}
	sh->f_built[0] = &ft_alias;
	sh->f_built[1] = &ft_cd;
	sh->f_built[2] = &ft_setenv;
	sh->f_built[3] = &ft_unsetenv;
//	sh->f_built[4] = &ft_exit;
//	sh->f_built[5] = &ft_env;
	sh->f_built[6] = &ft_echo;
}
