#include "../../includes/sh.h"

void sub_ar(t_shell *sh, char **arg, int i)
{
	char *todel[3];

	if ((*arg)[i++] != '$' || (*arg)[i++] != '(')
		return ;
	if (parenth(arg, i, (*arg)[i] == '(' ? '\0' : '`'))
		return ;
	todel[2] = *arg;
	(*arg)[i - 2] = ' ';
	(*arg)[i - 1] = ' ';
	if ((*arg)[i] != '(')
	{
		comm_substitute(sh, arg, i);
		return ;
	}
	mallcheck(*todel = ft_strndup(*arg, i - 2));
	if (!(*todel = parse_op(*arg)))
		todel[1] = ft_strnew(1);
	mallcheck(*arg = ft_implode(todel[1], *todel, &(*arg)[ft_strlen(*arg) + 1]));
	ft_memdel((void**)&(*todel));
	ft_memdel((void**)&todel[1]);
	ft_memdel((void**)&(*todel[2]));
}
