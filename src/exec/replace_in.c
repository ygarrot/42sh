

#include "../../includes/sh.h"

void recc_repl(t_tb **list)
{
	if (!list)
		return ;
	if ((*list)->next)
	{
		(*list)->str = (*list)->next->str;
		recc_repl(&(*list)->next);
	}
	else
		ft_memdel((void**)&(*list));
}

void add_glob(t_com *com, t_tb **list, char *str)
{
	if (!str)
	{
		recc_repl(list);
		return ;
	}
	if (((*list)->glob = ft_glob(str, 0)))
		ft_memdel((void**)&(*list)->str);
	com->len += (*list)->str ? 1 : (*list)->glob->nb_paths;
}

void replace_in(t_shell *sh, t_com *com)
{
	t_tb	*list;
	int		i;
	char *free;

	i = 0;
	free = NULL;
	list = com->tb;
	while (list)
	{
		free = list->str;
		list->str = ft_find_and_replace(free, "\\", 1);
		replace_local(&list->str, i++);
		ft_memdel((void**)&free);
		arg_replace(sh, &list->str);
		add_glob(com, &list, list->str);
		list ? list = list->next : 0;
	}
	if (!com->len)
		ft_memdel((void**)&com->cli);
	else
		epur_tb(com, com->len);
}
