/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:21:32 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 10:16:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

char	*ft_getenv(char **tb, char *str)
{
	int	len;

	if (!tb || !str)
		return (NULL);
	len = ft_strlen(str);
	while (*tb && (ft_strncmp(*tb, str, len) || tb[0][len] != '='))
		tb++;
	return (*tb);
}

void	reset_std(t_shell *sh, t_com *com, t_redi *redi)
{
	if (ft_strisin_tab(*com->cli, FBUILT, 0) >= 0
			|| (sh->com->next && sh->com->next->type & 4))
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

void	set_redi_path(t_redi *redi)
{
	int		fd;
	char	*tmp;

	if (redi->type)
		return ;
	tmp = redi->path;
	mallcheck(redi->path = (char*)ft_memalloc(18 * (sizeof(char))));
	ft_strcpy(redi->path, "/tmp/.sh_heredoc");
	redi->path[16] = redi->fd[0] + '0';
	fd = open(redi->path, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd < 0 || close(fd) < 0)
		ft_printf("Erreur lors du nettoyage des here_doc\n");
	ft_memdel((void**)&tmp);
}

