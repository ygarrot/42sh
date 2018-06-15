/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:11:38 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 16:15:17 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		*ft_subshell(void)
{
	static int	i = 0;

	return (&i);
}

int		ft_subshell_get(void)
{
	int	*i;

	i = ft_subshell();
	if (i)
		return (*i);
	return (0);
}

void	ft_subshell_set(int val)
{
	int	*i;

	i = ft_subshell();
	if (i)
		*i = val;
}
