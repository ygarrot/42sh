#include "../../includes/sh.h"


#define PARENTH 3
#define INCREMENT 0xF000000
typedef struct s_do_op 
{
    struct s_do_op *prev;
    struct s_do_op *next;
    char *content;
	bool	is_set;
	int		value;
	int		code;
}		t_do_op;

void	free_op(t_do_op *tmp)
{
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp->content);
}

int		inc(t_do_op *list)
{
	if (!list->prev->content || ft_str_isdigit(list->prev->content))
		return (-ft_printf("error\n"));
	if 

}

int browse_list(t_do_op *list)
{
	t_do_op *tmp;

	while (list)
	{
		if (list->code == INCREMENT)
			list->value++;
		if (list->code == PARENTH)
			parse_op(list->content);
		if (list->code != 2)
			continue ;
		list->value = do_op();
		tmp = list->next->next->next;
		free_op(list->next);
		free_op(list->next->next);
		list->next = tmp;
	}
	return (browse_last(list));
}

void	set_assign(t_do_op *list)
{
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if (list->code < 10 && list->code >= 0)
			list->prev->value = browse_list(list);
		list = list->prev;
	}
}

int		browse_last(t_do_op *list)
{
	t_do_op	*tmp;
	int		res;

	while (list)
	{
		if ()
	}
}

void	init_list(char **tb)
{
	t_do_op		*list;
	t_do_op		*begin;
	int			i;

	i = 0;
	while (tb)
	{
		tb[i + 1] ? list->next = (t_do_op*)ft_memalloc(sizeof(t_do_op)) : 0;
		list->next ? list->next->prev = list : 0;
		list->content =
			(list->code = get_sep(tb[i], OPE) < 0) ? tb[i] : 0;
	}
	ft_memdel((void**)&tb);
}
