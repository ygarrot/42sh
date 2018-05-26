/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 16:42:56 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/25 15:05:02 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*ft_completion_getfilename_(char *str, int loc, int bl, int sep)
{
	char	*res;

	if (loc == 0)
		res = ft_straddsep(str, bl, sep);
	else if (loc == -1)
		res = ft_strdup(" ");
	else
		res = 0;
	ft_strdel(&str);
	return (res);
}

char		*ft_completion_getfilename(char *left, int loc, int bl, int sep)
{
	char		*right;
	size_t		i;
	DIR			*dir;
	t_dirent	*file;

	if (loc <= 0 || !left || (*left == '~' && !left[1]))
		return (0);
	if (!(dir = ft_opendirfree(ft_getdir(left))))
		return (0);
	left = ((*left == '~') ? (left + 1) : (left));
	if (ft_isin('/', left))
		left += ft_strlento_rev(left, ft_strlen(left), "/") + 1;
	i =  ft_strlen(left);
	right = 0;
	while (loc > 0 && (file = readdir(dir)))
	{
		if (file->d_name[0] != '.' && !ft_strncmp(left, file->d_name, i))
			loc--;
		if (loc == 0 && ft_strlen(file->d_name) != i)
			right = ft_strdup(&(file->d_name)[i]);
		else if (loc == 0)
			loc = -1;
	}
	closedir(dir);
	return (ft_completion_getfilename_(right, loc, bl, sep));
}
