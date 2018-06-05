/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:39:20 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/26 16:06:26 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		ft_unsetenv(char **arg, char ***env)
{
	int		i;
	int		j;
	int		k;

	if (!arg || !env || !*env || (i = 0))
		write(STDOUT_FILENO, "\n", 1);
	else if (!*arg || !arg[1] || (k = 0))
		ft_printf("21sh: unsetenv: Argument missing\n");
	else if (arg[2])
		ft_printf("21sh: unsetenv: Too many arguments\n");
	else if ((j = ft_strlen(arg[1])) || 1)
	{
		while (env[0][i] &&
				(ft_strncmp(env[0][i], arg[1], j) || env[0][i][j] != '='))
			i++;
		k = (env[0][i] != 0);
		ft_strdel(&env[0][i]);
		while (env[0][i + k])
		{
			env[0][i] = env[0][i + k];
			i++;
		}
		if (k)
			env[0][i] = 0;
	}
}
