/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:51:31 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 15:24:52 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	mallcheck(void *foo)
{
	if (!foo)
		exit(EXIT_FAILURE);
}

void	parse_exe(t_shell *sh, char *comm, char **arg)
{
	int	index;

	if (exec_redi(sh, sh->com->redi) < 0)
		exit(error_exec(arg, 1));
	if (!ft_strcmp(comm, "env"))
		ft_env(sh, arg, &sh->env);
	else if ((index = ft_strisin_tab(arg[0], BUILT, 0)) >= 0)
		exit(1);
	else if ((index = ft_strisin_tab(arg[0], FBUILT, 0)) >= 0)
		sh->f_built[index](arg, &sh->env);
	else if (execve(comm, arg, sh->env))
	{
		error_exec(arg, 0);
		sh->status = 256;
		exit(EXIT_FAILURE);
	}
}

int		error_exec(char **argv, int is_redi)
{
	if (!is_redi)
		ft_printf("Command not found %s\n", *argv);
	return (-1);
}
