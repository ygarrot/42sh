#include "../../includes/sh.h"

int	error_do_op(char *str)
{
	ft_printf("%s", str);
	free_do_op(begin_op(NULL));
	return (-1);
}