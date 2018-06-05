#include "../../includes/sh.h"

void sub_ar(t_shell *sh, char **arg, int i)
{
	char *todel[3];

	if ((*arg)[i++] != '$' || (*arg)[i++] != '(')
		return ;
	if (parenth(arg, i - 2, (*arg)[i] == '(' ? '\0' : '`', 0) < 0)
		return ;
	todel[2] = *arg;
	if ((*arg)[i] != '(')
	{
		(*arg)[i - 2] = '`';
		(*arg)[i - 1] = ' ';
		comm_substitute(sh, arg, i);
		return ;
	}
	*todel = ft_strndup(*arg, i - 2 );
	!*todel ? *todel = ft_strnew(1) : 0;
	if (!(todel[1] = parse_op(&(*arg)[i + 1])))
		todel[1] = ft_strnew(1);
	mallcheck(*arg = ft_implode(todel[1], *todel, &(*arg)[ft_strlen(*arg) + 2]));
	ft_memdel((void**)&(*todel));
	ft_memdel((void**)&todel[1]);
	ft_memdel((void**)&todel[2]);
}
