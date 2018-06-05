#include "sh.h"

void mallcheck(void *foo){if (!foo) {exit(EXIT_FAILURE);}}

void	apply(void *item)
{
	printf("%s && %s\n", ((t_variable*)item)->name, ((t_variable*)item)->str);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_btree	**root;
	char	***s;

	(void)ac;
	(void)av;
	str = 0;
	ft_storeenv(ft_strtbdup(env));
	while (1)
	{
		if (get_next_line(0, &str) != 1)
			return (0);
		if (str[0] == '$')
			ft_printf("%s | %s\n", str, ft_variablepars(str));
		else if (str[0] == '!')
		{
			printf("\n");
			root = ft_variable();
			if (root && *root)
				btree_apply_infix(*root, &apply);
			else
				printf("ERROR\n");
		}
		else if (str[0] == '~')
		{
			printf("\n");
			root = ft_variable();
			if (root && *root)
				btree_apply_prefix(*root, &apply);
			else
				printf("ERROR\n");
		}
		else if (!ft_strcmp(str, "env"))
		{
			s = ft_storeenv(0);
			ac = 0;
			while (s[0][ac])
				printf("%s\n", s[0][ac++]);
		}
		else if (!ft_strncmp(str, "unset ", 6))
		{
			av = (char*[4]){"unset", &str[6], 0};
			s = ft_storeenv(0);
			ft_unset(av, s);
		}
		else if (!ft_strncmp(str, "export ", 7))
		{
			av = (char*[4]){"export", &str[7], 0};
			s = ft_storeenv(0);
			ft_export(av, s);
		}
		else
			ft_variable_builtin(str);
	}
}
