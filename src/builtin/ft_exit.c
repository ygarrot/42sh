/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:58:27 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 12:48:48 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_exit(t_shell *sh, int val)
{
	ft_terminal_reset(0);
	erase_shell(sh);
	ft_printf("exit\n");
	exit(val);
}
