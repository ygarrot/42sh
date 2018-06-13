/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:46 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 11:46:36 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_initstruct(t_read *data)
{
	if (!data)
		return ;
	data->delim = ft_strdup("\n");
	data->variables = 0;
	data->deep = 1;
	data->readline = 0;
	data->readline_active = 0;
	data->nchars = 0;
	data->nchars_exact = 0;
	data->prompt = 0;
	data->bl_active = 1;
	data->echo = 1;
	data->fd = STDIN_FILENO;
	data->error = 0;
	data->nchars_exact = 0;
	data->timer.tv_sec = 0;
	data->timer.tv_nsec = 0;
}
