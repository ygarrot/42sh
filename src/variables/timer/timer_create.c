#include <signal.h>
#include <time.h>
#include <stdio.h>

void	sig(int sig)
{
	printf("sig was called, %d\n", sig == SIGUSR1);
}

int	main(void)
{
	int	clock;
	struct sigevent	sevp;
	timer_t	timer_id;
	struct itimerspec	timer_set;

	if (signal(SIGUSR1, &sig) == SIG_ERR)
	{
		printf("Failed to set the signal\n");
		return (-1);
	}
	sevp.sigev_notify = SIGEV_SIGNAL;
	sevp.sigev_signo = SIGUSR1;
	timer_id = 0;
//	sevp.sigev_notify_thread_id = getpid();
	clock = timer_create(CLOCK_REALTIME, &sevp, &timer_id);
	if (clock == -1)
		printf("timer_create() failed\n");
	else
		printf("timer_create() succeded, timer = %p\n", timer_id);
	timer_set.it_interval.tv_sec = 0;
	timer_set.it_interval.tv_nsec = 0;
	timer_set.it_value.tv_sec = 10;
	timer_set.it_value.tv_nsec = 0;
	clock = timer_settime(timer_id, 0, &timer_set, 0);
	while (1)
		;
	return (0);
}
