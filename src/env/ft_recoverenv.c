/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recoverenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 10:53:46 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 13:04:52 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** -1 => Error
** 0 => No modification
** 1 => Modification
*/

int		ft_envmodiftime(char *file)
{
	static time_t	time = -1;
	t_stat			buff;
	time_t			i;

	if (!file || lstat(file, &buff) == -1)
		return (-1);
	i = time;
	time = buff.st_mtimespec.tv_sec;
	return (i != -1 && i != time);
}

int		ft_recoverenv(char ***env)
{
	char	*file;
	char	*line;
	int		fd;

	if (!(file = ft_getenvfile(CODE_ENVGET)))
		return (-1);
	if (ft_envmodiftime(file) != 1)
	{
		ft_strdel(&file);
		return (0);
	}
	fd = open(file, O_RDONLY);
	ft_strdel(&file);
	if (fd == -1)
		return (-1);
	ft_free_dblechar_tab(*env);
	*env = 0;
	line = 0;
	while (get_filetochar(fd, &line, '\v') == 1)
	{
		if (ft_dblstr_add(env, line) == -1)
			return (-1);
	}
	return (0);
}
