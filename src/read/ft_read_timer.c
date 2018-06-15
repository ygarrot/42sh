/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:33 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 15:45:43 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_timer_sig_interrup(int sig)
{
	static int	save = 0;
	int			tmp;

	tmp = sig;
	if (sig == SIGALRM)
		save = 1;
	else
		save = 0;
	return (tmp);
}

void	ft_read_timer_sig(int sig)
{
	if (sig == SIGALRM)
		ft_read_timer_sig_interrup(sig);
	printf("RING A BELL\n");
}

/*
** Cette fonction est adaptee a Linux :
**
** int		ft_read_timer(t_read *data)
** {
**	t_timer		timer_set;
**	t_sigevent	sevp;
**	timer_t		timer_id;
**
**	if (!data || data->error || (!data->timer.tv_sec && !data->timer.tv_nsec))
**		return (0);
**	if (signal(SIGUSR1, &ft_read_timer_sig) == SIG_ERR)
**		data->error = 1;
**	sevp.sigev_notify = SIGEV_SIGNAL;
**	sevp.sigev_signo = SIGUSR1;
**	if (data->error || timer_create(CLOCK_REALTIME, &sevp, &timer_id) == -1)
**		data->error = 1;
**	timer_set.it_interval.tv_sec = 0;
**	timer_set.it_interval.tv_nsec = 0;
**	timer_set.it_value.tv_sec = data->timer.tv_sec;
**	timer_set.it_value.tv_nsec = data->timer.tv_nsec;
**	if (data->error || timer_settime(timer_id, 0, &timer_set, 0) == -1)
**	{
**		data->error = 1;
**		ft_putstr_fd("21sh: read: Failed to set up the timer\n", 2);
**		return (-1);
**	}
**	return (0);
** }
*/

int		ft_read_timer(t_read *data)
{
	t_timer		timer_set;

	if (!data || data->error || (!data->timer.tv_sec && !data->timer.tv_nsec))
		return (0);
	if (signal(SIGALRM, &ft_read_timer_sig) == SIG_ERR)
		data->error = 1;
	timer_set.it_interval.tv_sec = 0;
	timer_set.it_interval.tv_usec = 0;
	timer_set.it_value.tv_sec = data->timer.tv_sec;
	timer_set.it_value.tv_usec = data->timer.tv_nsec / 1000;
	if (!timer_set.it_value.tv_usec && data->timer.tv_nsec)
		timer_set.it_value.tv_usec = 1;
	if (data->error || setitimer(ITIMER_REAL, &timer_set, 0) == -1)
	{
		data->error = 1;
		ft_putstr_fd("21sh: read: Failed to set up the timer\n", 2);
		return (-1);
	}
	return (0);
}
