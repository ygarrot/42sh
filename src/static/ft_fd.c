/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:54:53 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 12:02:11 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		*ft_fd(void)
{
	static int	save = 0;

	return (&save);
}

void	ft_fd_set(int val)
{
	int	*save;

	if ((save = ft_fd()))
		*save = val;
}

int		ft_fd_get(void)
{
	int	*save;

	if ((save = ft_fd()))
		return (*save);
	return (0);
}
