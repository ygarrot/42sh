/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 12:06:03 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:27:25 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_initenv(char ***env)
{
	char	*str;
	char	*arg[4];

	ft_memset((void*)arg, 0, sizeof(arg));
	if (!env || !*env)
		return ;
	str = getenv("SHLVL");
	arg[0] = "unsetenv";
	arg[1] = "SHLVL";
	ft_unsetenv(arg, env);
	arg[0] = "setenv";
	arg[2] = ft_itoa((str) ? (ft_atoi(str) + 1) : 1);
	ft_setenv(arg, env);
	if (!getenv("PWD"))
	{
		arg[1] = "PWD";
		arg[2] = getcwd(0, 1);
		ft_setenv(arg, env);
		free(arg[2]);
	}
	arg[1] = "TERM";
	if ((arg[2] = ttyname(0)))
		ft_setenv(arg, env);
	free(arg[2]);
}
