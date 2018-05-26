/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_save.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:25:55 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/25 14:56:50 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_completion_count(int code)
{
	static int	save = 0;

	if (code == CODE_RESET)
		save = 0;
	else if (code == CODE_PUSH)
		save++;
	else if (code == CODE_GET)
		return (save);
	return (0);
}

int			ft_completion_lastwrite(int code, int val)
{
	static int	save = 0;

	if (code == CODE_RESET)
		save = 0;
	if (code == CODE_SET)
		save = val;
	if (code == CODE_GET)
		return (save);
	return (0);
}

int			ft_completion_savetype(int code, int val)
{
	static int	save = 0;

	if (code == CODE_GET)
		return (save);
	else if (code == CODE_SET)
		save = val;
	else if (code == CODE_RESET)
		save = 0;
	return (0);
}

char		*ft_completion_saveleft(int code, char *left)
{
	static char	*save = 0;

	if (code == CODE_GET)
		return (save);
	else if (code == CODE_SET)
	{
		ft_memdel((void**)&save);
		save = left;
	}
	else if (code == CODE_RESET)
		ft_memdel((void**)&save);
	return (0);
}

int			ft_completion_reset(void)
{
	ft_completion_count(CODE_RESET);
	ft_completion_lastwrite(CODE_RESET, 0);
	ft_completion_savetype(CODE_RESET, 0);
	ft_completion_saveleft(CODE_RESET, 0);
	return (0);
}
