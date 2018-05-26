/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 11:46:02 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/25 15:05:19 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*ft_getdir_root(char *str, size_t i)
{
	while (i > 0 && str[i] != '/')
		i--;
	if (str[i] == '/')
		i++;
	return (ft_strndup(str, (int)i));
}

static char	*ft_getdir_home(char *str)
{
	char	*home;
	char	*res;
	size_t	i;

	if (!str)
		return (0);
	if (!(home = ft_getenvfromfile("HOME")))
		return (0);
	if ((i = ft_strlen(home)) < 5)
		ft_strdel(&home);
	if (!home)
		return (0);
	res = (char*)ft_memalloc(ft_strlen(str) + i);
	if (!res)
		ft_strdel(&home);
	if (!res)
		return (0);
	ft_strcat(res, &home[5]);
	res[i - 5] = (((i == 5 || res[i - 6] != '/') && str[1] != '/') ? ('/') : 0);
	if (ft_isin('/', &str[1]))
		ft_strncat(res, &str[1], ft_strlento_rev(&str[1], ft_strlen(str), "/"));
	i = ft_strlen(res);
	res[i] = ((i == 0 || res[i - 1] != '/') ? ('/') : (0));
	ft_strdel(&home);
	return (res);
}

char	*ft_getdir(char *str)
{
	char	*directory;
	char	*tmp;
	size_t	i;

	if (!str)
		return (0);
	if (*str == '/')
		return (ft_getdir_root(str, ft_strlen(str)));
	if (*str == '~')
		return (ft_getdir_home(str));
	if (!(tmp = getcwd(0, 0)))
		return (0);
	directory = (char*)ft_memalloc(ft_strlen(str) + 1 + ft_strlen(tmp));
	if (directory)
		ft_strcat(directory, tmp);
	ft_strdel(&tmp);
	if (!directory)
		return (0);
	i = ft_strlen(directory);
	if (i == 0 || directory[i - 1] != '/')
		directory[i] = '/';
	if (ft_isin('/', str))
		ft_strncat(directory, str, ft_strlento_rev(str, ft_strlen(str), "/"));
	return (directory);
}
