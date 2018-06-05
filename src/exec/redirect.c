/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 11:59:55 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/02 11:41:21 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** Ce programme effectue les changements pour x>fd
** Le format est le meme pour x>&fd (Simplement ne pas ouvrir le fichier)
*/

int		safe_dup(int fd1, int fd2, int *pipe)
{
	if (fd1 != -1 && dup2(fd1, fd2) == -1)
		return (-printf("dup error\n"));
	close(pipe[1]);
	close(pipe[0]);
	return (0);
}

int		stream(t_shell *sh, t_redi *redi)
{
	int		flag;
	int		right;

	if (!redi->type)
	{
		if (redi->fd[1] < 0 && (redi->fd[1] = open(redi->path,
						O_RDWR | O_CREAT | O_APPEND, S_IRWXU)) < 0)
			return (-ft_printf("21sh: no such file: %s\n", redi->path));
		ft_putstr_fd(sh->here_doc, redi->fd[1]);
		sh->here_doc += ft_strlen(sh->here_doc) + 1;
		close(redi->fd[1]);
		redi->fd[1] = -1;
	}
	right = !redi->type ? S_IRWXU : S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	flag = O_RDWR | (redi->type == 5 ? O_TRUNC : 0) |
		(!redi->type || redi->type == 5 ? O_CREAT : 0)
		| (redi->type == 1 ? O_APPEND : 0);
	if (redi->fd[1] < 0 && (redi->fd[1] = open(redi->path, flag, right)) < 0)
		return (-ft_printf("21sh: no such file: %s\n", redi->path));
	if (!sh->com->tmp && dup2(redi->fd[1], redi->fd[0]) == -1)
		return (-ft_printf("Failed to dup2\n"));
	if (sh->com->tmp)
		close(redi->fd[1]);
	return (1);
}

int		set_redi(t_shell *sh, t_redi *redi)
{
	redi->fd[1] = -1;
	if (sh->com->tmp && !redi->type)
		return (1);
	if (!sh->com->tmp && (redi->type == 2 || redi->type == 3))
	{
		if (!ft_strcmp(redi->path, "-"))
			return (close(redi->fd[0]));
		else
			redi->fd[1] = ft_atoi(redi->path);
	}
	return (stream(sh, redi));
}

int		exec_redi(t_shell *sh, t_redi *tmp)
{
	t_com	*co;
	int		ret;

	ret = 0;
	co = sh->com;
	while (tmp)
	{
		if (set_redi(sh, tmp) <= 0)
			return (-1);
		tmp = tmp->next;
	}
	if (((sh->com->type & 4 && sh->com->tmp)
	|| !(sh->com->type & 4)) && (sh->com->next && sh->com->next->type & 4))
	{
		sh->com = sh->com->next;
		sh->com->tmp = 1;
		ret = exec_redi(sh, sh->com->redi);
		sh->com->tmp = 0;
	}
	sh->com = co;
	return (ret);
}

int		exec_pipe(t_shell *sh, char *comm, char **argv)
{
	t_com	*tmp;
	pid_t	father;
	int		*pipe_fd;

	tmp = sh->com->next;
	pipe_fd = (tmp && tmp->type & 4 ? tmp->pipe : sh->sub.pipe);
	if (pipe(pipe_fd))
		return (-printf("Broken pipe\n"));
	father = fork();
	if (!father)
	{
		if (sh->com->type & 4 &&
				safe_dup(sh->com->pipe[0], STDIN_FILENO, sh->com->pipe))
			exit(EXIT_FAILURE);
		if (safe_dup(pipe_fd[1], STDOUT_FILENO, pipe_fd))
			exit(EXIT_FAILURE);
		parse_exe(sh, comm, argv);
		
	}
	else if (father < 0)
		return (-ft_printf("sh : fork error : %d", father));
	if (sh->com->type & 4)
		safe_dup(-1, 0, sh->com->pipe);
	return (1);
}
