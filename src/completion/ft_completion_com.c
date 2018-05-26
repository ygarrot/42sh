/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_com.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:51:09 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/25 13:00:05 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_completion_com_(char *left, int *loc, char *path, char **right)
{
	size_t		i;
	t_dirent	*file;
	DIR			*dir;

	if (!path || !left || !loc || !right)
		return ;
	if (!(dir = opendir(path)))
		return ;
	i = ft_strlen(left);
	while (loc[0] > 0 && (file = readdir(dir)))
	{
		if (!ft_strncmp(left, file->d_name, i))
			loc[0]--;
		if (*loc == 0 && ft_strlen(file->d_name) > i)
			*right = ft_strdup(&(file->d_name)[i]);
		else if (*loc == 0)
		{
			*right = ft_strdup(" ");
			*loc = -1;
		}
	}
	closedir(dir);
}

char	*ft_completion_com(char *left, int loc, int bl, int sep)
{
	char		*right;
	size_t		i[2];
	char		*path;

	if (!left)
		return (0);
	if (!(path = ft_getenvfromfile("PATH")))
		return (0);
	i[0] = 5;
	right = 0;
	while (loc > 0 && path[i[0]])
	{
		i[1] = i[0] + ft_strlento(&path[i[0]], ':');
		if (path[i[1]])
		{
			path[i[1]] = 0;
			i[1]++;
		}
		ft_completion_com_(left, &loc, &path[i[0]], &right);
		i[0] = i[1];
	}
	ft_strdel(&path);
	path = loc == -1 ? ft_strdup(" ") : ft_straddsep(right, bl, sep);
	ft_strdel(&right);
	return (path);
}
