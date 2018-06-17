/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:45:17 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 14:04:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		wait_exec(t_shell *sh, char **arg)
{
	char	*tmp;
	int		ind;

	if (!ft_strcmp(*arg, "exit"))
		ft_exit(sh, arg[1] ? ft_atoi(arg[1]) : EXIT_SUCCESS);
	if ((ind = ft_strisin_tab(arg[0], BUILT, 0)) >= 0)
	{
		if (exec_redi(sh, sh->com->redi) < 0)
			return (-1);
		if (sh->com->type & 4 || (sh->com->next && sh->com->next->type & 4))
			return (exe(sh, *arg, arg));
		sh->built[ind](arg, &sh->env);
		return (1);
	}
	if ((ind = ft_strisin_tab(arg[0], FBUILT, 0)) >= 0)
		return (exe(sh, *arg, arg));
	if (sh->hash_tb && (tmp = ft_get_hash(sh->hash_tb, *arg)))
		return (exe(sh, tmp, arg));
	if (!access(*arg, F_OK | X_OK))
	{
		ft_set_hash(sh->hash_tb, *arg, *arg);
		return (exe(sh, *arg, arg));
	}
	return (search_exec(sh, *arg, arg));
}

int		exe(t_shell *sh, char *comm, char **argv)
{
	pid_t father;

	if ((sh->com->next && sh->com->next->type & 4)
	|| (sh->sub.is_sub == 1 && (!sh->com->next || sh->com->next->type != 4)))
		return (exec_pipe(sh, comm, argv));
	father = fork();
	if (!father)
	{
		if (sh->com->type & 4 &&
				safe_dup(sh->com->pipe[0], STDIN_FILENO, sh->com->pipe))
			exit(EXIT_FAILURE);
		parse_exe(sh, comm, argv);
	}
	if (sh->com->type & 4)
		safe_dup(-1, 0, sh->com->pipe);
	if (father > 0)
		while (wait(&sh->status) != -1)
			;
	else
		return (-ft_printf("sh : fork error : %d", father));
	return (-WEXITSTATUS(sh->status));
}

int		search_exec(t_shell *sh, char *comm, char **argv)
{
	int		index;
	char	*temp;
	char	**paths;
	char	*path;

	temp = NULL;
	if (!comm || !(path = ft_getenv_fromroot("PATH")))
		return (!comm ? 0 : -ft_printf("command not found : %s\n", comm));
	mallcheck(paths = ft_strsplit(path, ':'));
	index = -1;
	while (!temp && paths[++index])
	{
		temp = ft_implode("/", paths[index], comm);
		sh->hash_tb && !access(temp, F_OK | X_OK) ?
			ft_set_hash(&sh->hash_tb[hash(comm) % HASH_SIZE], comm, temp) : 0;
		!access(temp, F_OK | X_OK) ? index = exe(sh, temp, argv) :
			ft_memdel((void**)&temp);
	}
	!temp && index >= 0 ? exe(sh, *argv, argv) : ft_memdel((void**)&temp);
	ft_free_dblechar_tab(paths);
	return (index >= 0 ? 1 : -1);
}

int		exec_cli(t_shell *sh, t_com *com)
{
	t_redi	*to_del;
	t_redi	*redi;
	int		fail;
	int		fd;

	if (!com->cli)
		return (1);
	fail = wait_exec(sh, com->cli);
	redi = com->redi;
	while (redi)
	{
		if (!redi->type)
		{
			sh->here_doc += ft_strlen(sh->here_doc) + 1;
			fd = open(redi->path, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (fd < 0 || close(fd) < 0)
				ft_printf("Erreur lors du nettoyage des here_doc\n");
		}
		reset_std(sh, com, redi);
		to_del = redi;
		redi = redi->next;
		ft_memdel((void**)&to_del->path);
		ft_memdel((void**)&to_del);
	}
	return (fail);
}

int		sort_comm(t_shell *sh)
{
	char	fail[2];
	t_com	*tmp;

	if (!sh || !sh->com || (!sh->begin && !(sh->begin = sh->com)))
		return (1);
	replace_in(sh, sh->com);
	while (!(tmp = NULL) && sh->com)
	{
		fail[1] = sh->com->next && sh->com->next->type & 4;
		ft_recoverenv(&sh->env) == -1 ? ft_errorlog(ENVFAILED) : 0;
		if (fail[1] && (tmp = sh->com))
		{
			*fail = exec_cli(sh, sh->com);
			sh->com = sh->com->next;
			*fail = sort_comm(sh);
		}
		else
			*fail = exec_cli(sh, sh->com);
		!fail[1] && *fail > 0 && sh->sub.is_sub == 1 ? get_sub(sh) : 0;
		if (((!tmp && sh->com) || (sh->com = tmp)) && sh->com->type & 4)
			return (*fail);
		shift_com(sh, *fail);
	}
	free_comm(sh);
	return (0);
}
