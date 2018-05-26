/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:39:20 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/15 13:09:03 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		ft_unsetenv(char **arg, char ***env)
{
	int		i;
	int		j;
	int		fd;

	if (!arg || !env || !*env || (i = 0))
		write(STDOUT_FILENO, "\n", 1);
	else if (!*arg || !arg[1])
		ft_printf("21sh: unsetenv: Argument missing\n");
	else if (arg[2])
		ft_printf("21sh: unsetenv: Too many arguments\n");
	else
	{
		j = ft_strlen(arg[1]);
		if ((fd = open(ft_getenvfile(CODE_ENVGET), O_WRONLY | O_CREAT |
						O_TRUNC)) < 0)
			exit(EXIT_FAILURE);
		while ((*env)[i])
		{
			i += (!ft_strncmp(arg[1], (*env)[i], j) && (*env)[i][j] == '=');
			ft_putendv_fd(env[0][i++], fd);
		}
		exit(close(fd) < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
