/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:56:40 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/15 13:52:24 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		ft_setenvno(char **arg, char ***env)
{
	int		i;
	size_t	j;
	int		fd;

	if (!arg || !env || !*env || (i = 0))
		write(STDOUT_FILENO, "\n", 1);
	else if (!*arg || !arg[1] || (j = ft_strlen(arg[1])) <= 0)
		ft_putendl_fd("21sh: setenv VARNAME [VARVALUE]", 2);
	else
	{
		if ((fd = open(ft_getenvfile(CODE_ENVGET), O_WRONLY | O_CREAT |
						O_TRUNC)) < 0)
			exit(EXIT_FAILURE);
		while ((*env)[i] && (ft_strncmp(arg[1], (*env)[i], j) ||
				(*env)[i][j] != '='))
			ft_putendv_fd(env[0][i++], fd);
		i += (env[0][i] != 0);
		ft_putstr_fd(arg[1], fd);
		ft_putstr_fd("=", fd);
		ft_putendv_fd(arg[2], fd);
		while ((*env)[i] && (ft_strncmp(arg[1], (*env)[i], j) ||
				(*env)[i][j] != '='))
			ft_putendv_fd(env[0][i++], fd);
		close(fd);
	}
}
