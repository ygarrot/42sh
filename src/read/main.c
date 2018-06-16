/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 12:06:05 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 14:55:22 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	main(int ac, char **av, char **env)
{
	t_variable	*v;
	(void)ac;

	ft_initsig();
	ft_read_builtin(&av[1], &env);
	v = ft_variableget("REPLY");
	if (v)
		printf("%s\n", v->str);
	return (0);
}
