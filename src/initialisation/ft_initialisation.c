/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 09:51:54 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/17 11:50:54 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_initialisation(char **env, t_shell *sh)
{
	ft_init_terminal_data(env);
	ft_initsig();
	if (ft_setattr() == -1)
		ft_fatal("Can't set terminal's attributes");
	if (!(sh->env = ft_strtbdup(env)))
		ft_fatal("Can't malloc the env");
	if (ft_envwrite(ft_getenvfile(CODE_ENVGET), sh->env) == -1)
	{
		ft_free_dblechar_tab(sh->env);
		ft_fatal("Can't copy the env");
	}
}
