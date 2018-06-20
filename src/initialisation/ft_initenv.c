/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 12:06:03 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 16:27:43 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_initenv(char ***env)
{
	char	*str;
	char	**arg;

	if (!env || !*env)
		return ;
	str = ft_getenv(*env, "SHLVL");
	arg = (char*[4]){"setenv", "SHLVL", ft_itoa(
		str && ft_strlen(str) > 6 ? ft_atoi(&str[6]) + 1 : 1), 0};
	ft_setenv(arg, env);
	ft_strdel(&arg[2]);
	if (!ft_getenv(*env, "PWD"))
	{
		arg = (char*[4]){"setenv", "PWD", getcwd(0, 1), 0};
		ft_setenv(arg, env);
		free(arg[2]);
	}
	if (!ft_getenv(*env, "TERM"))
		ft_setenv((char*[4]){"setenv", "TERM", "xterm-256color", 0}, env);
}
