/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 10:08:21 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:29:06 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_initsig(void)
{
	if (signal(SIGINT, ft_sig_line) == SIG_ERR)
		ft_fatal("Failed to catch CRL+C, exit ...");
}

void	ft_sig_line(int sig)
{
	if (sig == SIGINT)
		ft_sigint(SIGINT);
}
