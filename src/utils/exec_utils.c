/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:21:32 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/26 12:03:02 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

char	*ft_getenv(char **tb, char *str)
{
	int	i;
	int	len;

	i = 0;
	if (!tb || !str)
		return (NULL);
	len = ft_strlen(str);
	while (*tb && (ft_strncmp(*tb, str, len) || tb[0][len] != '='))
		tb++;
	return (*tb);
}

void	reset_std(t_shell *sh, t_com *com, t_redi *redi)
{
	if (ft_strcmp(*com->cli, "cd"))
		return ;
	if ((redi->type == 2 || redi->type == 3)
			&& !ft_strcmp(redi->path, "-") && redi->fd[0] < 3)
	{
		if (dup2(sh->std[redi->fd[0]], redi->fd[0]) == -1)
			ft_printf("STDIN dup error\n");
		return ;
	}
	if (close(redi->fd[1]) == -1)
		ft_printf("21sh: close error on %s\n", com->redi->path);
	if (redi->fd[0] < 3 && dup2(sh->std[redi->fd[0]], redi->fd[0]) == -1)
		ft_printf("STDIN dup error\n");
}
