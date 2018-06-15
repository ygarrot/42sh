/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 09:51:54 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 16:39:21 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_initialisation(char **env, t_shell *sh)
{
	char	***check;

	ft_init_terminal_data();
	ft_initsig();
	if (ft_setattr() == -1)
		ft_fatal("Can't set terminal's attributes");
	if (!(check = ft_storeenv(ft_strtbdup(env), 0)))
		ft_fatal("A fatal error occured");
	if (!*check)
		ft_fatal("A fatal error occured");
	if (!(sh->env = *check))
		ft_fatal("Can't malloc the env");
}
