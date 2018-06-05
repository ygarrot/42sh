/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:18:21 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/27 15:36:32 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_echo(char **arg, char ***en)
{
	char	**env;

	env = *en;
	if (arg && env && *arg)
	{
		arg++;
		while (*arg)
		{
			ft_putstr(*arg);
			arg++;
			if (*arg)
				ft_printf(" ");
		}
	}
	ft_printf("\n");
	exit(0);
}
