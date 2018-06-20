/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 09:53:12 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 12:30:15 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_fatal(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	ft_errorlog(str);
	exit(0);
}

char	*ft_conversion_error(int code)
{
	if (code == MALLOC_ERR)
		ft_putstr_fd(MALLOC_ERR_MSG, 2);
	else if (code == PARSING_ERROR_3)
		ft_putstr_fd(PARSING_ERROR_3_MSG, 2);
	else if (code == PARSING_ERROR_4)
		ft_putstr_fd(PARSING_ERROR_4_MSG, 2);
	return (0);
}

int		ft_error(char *str, char *arg)
{
	ft_putendl_fd(str, 2);
	ft_putendl_fd(arg, 2);
	return (-1);
}

void	ft_errorlog(char *msg)
{
	int		fd;

	if (!msg)
		return ;
	if ((fd = open(LOGFILE, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) < 0)
		return ;
	ft_putendl_fd(msg, fd);
	close(fd);
}
