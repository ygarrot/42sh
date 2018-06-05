/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_tour.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 11:32:12 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/26 15:35:41 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

t_paths		*path_is_valid(char *path, char *name, t_dirent *dir, char **regex)
{
	struct stat	st;
	t_paths		*tmp;

	if ((*dir->d_name == '.' && **regex != '.') || !ft_match(name, *regex))
		return (NULL);
	name ? path = ft_strjoin(path, name) : 0;
	if (stat(path, &st) == -1 && lstat(path, &st) == -1)
	{
		ft_memdel((void**)&path);
		return (NULL);
	}
	mallcheck(tmp = (t_paths*)ft_memalloc(sizeof(t_paths)));
	tmp->is_dir = (st.st_mode & S_IFMT) == S_IFDIR ? 1 : 0;
	(st.st_mode & S_IFMT) == S_IFLNK ? lstat(path, &st) : 0;
	lstat(path, &st);
	tmp->path = path;
	mallcheck(tmp->name = ft_strdup(name));
	return (tmp);
}

t_paths		*end_sort(t_paths *tmp, char *str, char **regex)
{
	t_paths	*to_del;
	t_paths	*begin;

	regex = &regex[1];
	begin = *regex && **regex ? NULL : tmp;
	while (tmp)
	{
		if (*regex && **regex && tmp->is_dir)
		{
			!tmp->path ? mallcheck(tmp->path = ft_strjoin(str, tmp->name)) : 0;
			if (!begin)
				begin = recc(tmp->path, regex);
			else
				true_sort(begin, recc(tmp->path, regex));
		}
		to_del = tmp;
		tmp = tmp->next;
		if (!*regex)
			continue ;
		ft_memdel((void**)&to_del->name);
		ft_memdel((void**)&to_del->path);
		ft_memdel((void**)&to_del);
	}
	return (begin);
}

t_paths		*files_queue(char *str, DIR *dire, char **regex)
{
	t_dirent	*dir;
	t_paths		*tmp;
	t_paths		*begin;

	begin = NULL;
	while (!begin && (dir = readdir(dire)))
		begin = path_is_valid(str, dir->d_name, dir, regex);
	while ((dir = readdir(dire)))
		if ((tmp = path_is_valid(str, dir->d_name, dir, regex)))
			true_sort(begin, tmp);
	return (begin);
}

t_paths		*recc(char *str, char **regex)
{
	t_paths		*begin;
	DIR			*dire;

	dire = opendir(str);
	if (!dire)
		return (NULL);
	mallcheck(str = ft_strjoin(str, "/"));
	begin = files_queue(str, dire, regex);
	begin ? begin = end_sort(begin, str, regex) : 0;
	ft_memdel((void**)&str);
	closedir(dire);
	return (begin);
}

t_glob		*ft_glob(char *regstr, int opt)
{
	t_paths		*begin;
	t_paths		*tmp;
	char		**regtab;
	t_glob		*glob;
	int			len;

	(void)opt;
	if (!regstr || !ft_strcmp(regstr, "/"))
		return (NULL);
	mallcheck(glob = (t_glob*)ft_memalloc(sizeof(t_glob)));
	ft_bzero(glob, sizeof(glob));
	mallcheck(regtab = ft_strsplit_comm(regstr, "/"));
	begin = recc(*regstr == '/' ? "/" : ".", regtab);
	tmp = begin;
	len = *regstr == '/' ? 1 : 2;
	while (tmp)
	{
		ft_strcpy(tmp->path, &tmp->path[len]);
		glob->nb_paths++;
		tmp = tmp->next;
	}
	glob->paths = begin;
	ft_free_dblechar_tab(regtab);
	(!begin) ? ft_memdel((void**)&glob) : 0;
	return (glob);
}
