#include "sh.h"

void	ft_fatal(char *str)
{exit(0);}

int	main(int ac, char **av)
{
	t_read	p;

	av[ac] = 0;
	av[0] = "read";
	p = ft_read_parser(av);

	printf("		delim : %c\n\
		deep : %d\n\
		readline : %s\n\
		readline_active : %d\n\
		nchars : %lu\n\
		nchars_exact : %lu\n\
		prompt : %s\n\
		bl_active : %d\n\
		echo : %d\n\
		timer : %ld.%.8ld\n\
		fd : %d\n\
		error : %d\n"
			, p.delim == '\n' ? 'N' : p.delim, p.deep, p.readline, p.readline_active,\
			p.nchars, p.nchars_exact,\
			p.prompt, p.bl_active, p.echo, p.timer.tv_sec, p.timer.tv_nsec,\
			p.fd, p.error);

	ac = 0;
	while (p.variables && p.variables[ac])
	{
		printf("		%d >> %s\n", ac, p.variables[ac]);
		ac++;
	}
	if (ft_read_timer(&p) == -1)
		exit (-1);
	if (ft_read_assign(&p, "Cette  chaine  dit .  \n") == -1)
	{
		dprintf(2, "An error occured\n");
		return (-1);
	}
	else
		dprintf(2, "Assign is ok\n");
	ac = 0;
	while (p.variables && p.variables[ac])
	{
		printf("%s | %s\n", p.variables[ac], ft_variablepars(p.variables[ac]));
		ac++;
	}
	return (0);
}
