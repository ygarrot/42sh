/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:31:22 by tcharrie          #+#    #+#             */
/*   Updated: 2018/04/23 16:29:11 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

char	*ft_selected(char *str, int code)
{
	static char	*s = 0;

	if (code == CODE_GET)
		return (s);
	if (code == CODE_SET)
	{
		ft_strdel(&s);
		s = str;
	}
	return (0);
}

int		ft_selected_moveleft(t_line *line, int *val)
{
	char	*str;

	if (val[0] <= val[5] || !line)
		return (1);
	if (!(str = val[4] ? line->line : line->eof))
		return (-1);
	if (val[2]-- == 1)
		return (ft_selected(0, CODE_SET) ? 0 : 0);
	if (str[val[0] - 1] == '\n')
		return (1);
	if (ft_move_left(line, val) == -1)
		return (-1);
	ft_printf((val[2] < 0) ? ("{blackcyan}%.*s") : ("{whiteblack}%.*s"),
			ft_lenchar_r(str, val[0]), &str[val[0]]);
	val[0] += ft_lenchar_r(str, val[0]);
	ft_move_left(line, val);
	return (1);
}

int		ft_selected_moveright(t_line *line, int *val)
{
	char	*str;

	if (!line || !(str = val[4] ? line->line : line->eof))
		return (-1);
	if ((val[6] = tgetnum("co")) <= 1)
		return (-1);
	if (!(str[val[0]]) || str[val[0]] == '\n')
		return (1);
	if (val[2]++ == -1)
		return (ft_selected(0, CODE_SET) ? 0 : 0);
	ft_printf((val[2] > 0) ? ("{blackcyan}%.*s") : ("{whiteblack}%.*s"),
			ft_lenchar_r(str, val[0]), &str[val[0]]);
	val[0] += ft_lenchar_r(str, val[0]);
	if (ft_lenline_v(str, val[0]) % val[6] == 0)
		ft_getdown();
	return (1);
}

int		ft_selected_cpy(t_line *line, int *val)
{
	char	*str;
	char	*sel;
	int		size;

	if (!line || !(str = (val[4] ? line->line : line->eof)))
		return (-1);
	if (val[2] > 0)
		size = ft_lennchar_l(str, val[0], val[2]);
	else
		size = ft_lennchar_r(str, val[0], -val[2]);
	if (val[2] == 0 || size == 0)
		return (1);
	if (!(sel = (char*)ft_memalloc(size + 1)))
		return (-1);
	if (val[2] > 0)
		ft_strncat(sel, &str[val[0] - size], (size_t)size);
	else if (val[2] < 0 && val[0] >= -size)
		ft_strncat(sel, &str[val[0]], (size_t)size);
	ft_selected(sel, CODE_SET);
	return (1);
}

int		ft_selected_paste(t_line *line, int *val)
{
	char	*sel;

	if (!(sel = (char*)ft_selected((char*)0, (int)CODE_GET)))
		return (1);
	return (ft_printstr(line, sel, val));
}
