/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envwrite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:07:02 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/15 18:34:09 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_envwrite(char *file, char **env)
{
	int	fd;

	if (!env || (fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0)
		return (-1);
	ft_memdel((void**)&file);
	while (*env)
	{
		write(fd, *env, ft_strlen(*env));
		write(fd, "\v", 1);
		env++;
	}
	return (0);
}
