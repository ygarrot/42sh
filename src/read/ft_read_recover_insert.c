/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover_insert.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 11:25:39 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 12:37:55 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_read_recover_insert(t_line *line, int *val, char *buff, int len)
{
	size_t	l;

	ft_strdel(&line->eof);
	l = ft_strlen(line->line);
	if (!(line->eof = (char*)ft_memalloc(l + len + 1)))
		return ;
	line->eof[0] = 0;
	ft_strncat(line->eof, line->line, val[0]);
	ft_strncat(&(line->eof[val[0]]), buff, len);
	ft_strcat(&(line->eof)[val[0]], &(line->line)[val[0]]);
	ft_strdel(&(line->line));
	line->line = line->eof;
	line->eof = 0;
	val[0] += len;
}

int		ft_read_recover_execute(t_line *line, int *val, char *buff, int echo)
{
	int	i;

	if ((i = ft_strprefix(KEY_COMPLETION, buff)))
		return (i);
	else if ((i = ft_strprefix(KEY_SELECT_LEFT, buff)))
		return (i);
	else if ((i = ft_strprefix(KEY_SELECT_RIGHT, buff)))
		return (i);
	else if ((i = ft_strprefix(KEY_SELECT_CPY, buff)))
		return (i);
	else if ((i = ft_strprefix(KEY_SELECT_PASTE, buff)))
		return (i);
	else if ((i = ft_strprefix(KEY_LEFT, buff)))
		echo ? ft_move_left(line, val) : ft_read_move_left(line, val);
	else if ((i = ft_strprefix(KEY_LEFT_SHIFTED, buff)))
		echo ? ft_move_wordl(line, val) : ft_read_move_wordl(line, val);
	else if ((i = ft_strprefix(KEY_RIGHT, buff)))
		echo ? ft_move_right(line, val) : ft_read_move_right(line, val);
	else if ((i = ft_strprefix(KEY_RIGHT_SHIFTED, buff)))
		echo ? ft_move_wordr(line, val) : ft_read_move_wordr(line, val);
	else if ((i = ft_strprefix(KEY_HOME, buff)))
		echo ? ft_move_tohome(line, val) : ft_read_move_tohome(line, val);
	else
		return (ft_read_recover_execute_a(line, val, buff, echo));
	return (i);
}

int		ft_read_recover_execute_a(t_line *line, int *val, char *buff, int echo)
{
	int	i;

	if ((i = ft_strprefix(KEY_HOME_SHIFTED, buff)))
		echo ? ft_move_tolinel(line, val) : ft_read_move_tolinel(line, val);
	else if ((i = ft_strprefix(KEY_END, buff)))
		echo ? ft_move_toend(line, val) : ft_read_move_toend(line, val);
	else if ((i = ft_strprefix(KEY_END_SHIFTED, buff)))
		echo ? ft_move_toliner(line, val) : ft_read_move_toliner(line, val);
	else if ((i = ft_strprefix(KEY_ERASE, buff)))
		echo ? ft_erase(line, val) : ft_read_erase(line, val);
	else if ((i = ft_strprefix(KEY_DELETE, buff)))
		echo ? ft_delete(line, val) : ft_read_delete(line, val);
	else if ((i = ft_strprefix(KEY_UP, buff)))
		echo ? ft_move_tohist(line, val, 1) : ft_read_movetohist(line, val, 1);
	else if ((i = ft_strprefix(KEY_UP_SHITED, buff)))
		echo ? ft_move_up(line, val) : ft_read_move_up(line, val);
	else if ((i = ft_strprefix(KEY_DOWN, buff)))
		echo ? ft_move_tohist(line, val, -1) :
			ft_read_movetohist(line, val, -1);
	else if ((i = ft_strprefix(KEY_DOWN_SHIFTED, buff)))
		echo ? ft_move_down(line, val) : ft_read_move_down(line, val);
	else if ((i = ft_strprefix(NEWLINE, buff)))
		ft_read_recover_insert(line, val, buff, 1);
	return (i);
}
