/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:47:33 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 11:12:12 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_specialchar(t_line *line, char *str, int *val)
{
	int	i;

	i = 0;
	if (!ft_strprefix(KEY_COMPLETION, str))
		ft_completion_reset();
	if (ft_isin(*str, "\r\f\v"))
		return (1);
	else if ((i = ft_strprefix(KEY_SELECT_LEFT, str)))
		ft_selected_moveleft(line, val);
	else if ((i = ft_strprefix(KEY_SELECT_RIGHT, str)))
		ft_selected_moveright(line, val);
	else if ((i = ft_strprefix(KEY_SELECT_CPY, str)))
		ft_selected_cpy(line, val);
	else if ((i = ft_strprefix(KEY_SELECT_PASTE, str)))
		ft_selected_paste(line, val);
	else if (val[2])
	{
		ft_selected_reset(line, val);
		ft_completion_reset();
		i = ft_lenchar_joker(str);
	}
	else
		return (ft_specialchar_a(line, str, val));
	return (i);
}

int		ft_specialchar_b(t_line *line, char *str, int *val)
{
	int	i;

	i = 0;
	if ((i = ft_strprefix(KEY_RIGHT, str)))
		ft_move_right(line, val);
	else if ((i = ft_strprefix(KEY_LEFT_SHITED, str)))
		ft_move_wordl(line, val);
	else if ((i = ft_strprefix(KEY_RIGHT_SHIFTED, str)))
		ft_move_wordr(line, val);
	else if ((i = ft_strprefix(KEY_HOME, str)))
		ft_move_tohome(line, val);
	else if ((i = ft_strprefix(KEY_HOME_SHIFTED, str)))
		ft_move_tolinel(line, val);
	else if ((i = ft_strprefix(KEY_END_SHIFTED, str)))
		ft_move_toliner(line, val);
	else if ((i = ft_strprefix(KEY_ERASE, str)))
		ft_erase(line, val);
	else if ((i = ft_strprefix(KEY_DELETE, str)))
		ft_delete(line, val);
	return (i);
}

int		ft_specialchar_a(t_line *line, char *str, int *val)
{
	int	i;

	i = 0;
	if ((i = ft_strprefix(KEY_COMPLETION, str)))
		ft_completion(line, val);
	else if ((i = ft_strprefix(KEY_UP_SHITED, str)))
		ft_move_up(line, val);
	else if ((i = ft_strprefix(KEY_DOWN_SHITED, str)))
		ft_move_down(line, val);
	else if ((i = ft_strprefix(KEY_END, str)))
		ft_move_toend(line, val);
	else if ((i = ft_strprefix(KEY_UP, str)))
		ft_move_tohist(line, val, 1);
	else if ((i = ft_strprefix(KEY_DOWN, str)))
		ft_move_tohist(line, val, -1);
	else if ((i = ft_strprefix(KEY_LEFT, str)))
		ft_move_left(line, val);
	else
		return (ft_specialchar_b(line, str, val));
	return (i);
}

int		ft_lentospecial(char *str)
{
	int		i;
	int		j;
	char	**specialchar;

	specialchar = (char*[22]){KEY_LEFT, KEY_LEFT_SHITED, KEY_RIGHT,
	KEY_RIGHT_SHIFTED, KEY_UP, KEY_UP_SHITED, KEY_DOWN, KEY_DOWN_SHITED,
	KEY_SELECT_LEFT, KEY_SELECT_RIGHT, KEY_SELECT_CPY, KEY_SELECT_PASTE,
	KEY_END, KEY_END_SHIFTED, KEY_HOME, KEY_HOME_SHIFTED, KEY_DELETE,
	KEY_ERASE, NEWLINE, KEY_COMPLETION, "\4", 0};
	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (specialchar[j])
		{
		if (!ft_strncmp(specialchar[j], &str[i], ft_strlen(&str[i])) &&
				ft_strlen(specialchar[j]) > ft_strlen(&str[i]))
				return (i ? i - 1 : 0);
			j++;
		}
		i++;
	}
	return (i);
}

int		ft_lenchar_joker(char *str)
{
	int		i;
	int		j;
	char	**specialchar;

	if (!str)
		return (0);
	specialchar = (char*[22]){KEY_LEFT, KEY_LEFT_SHITED, KEY_RIGHT,
	KEY_RIGHT_SHIFTED, KEY_UP, KEY_UP_SHITED, KEY_DOWN, KEY_DOWN_SHITED,
	KEY_SELECT_LEFT, KEY_SELECT_RIGHT, KEY_SELECT_CPY, KEY_SELECT_PASTE,
	KEY_END, KEY_END_SHIFTED, KEY_HOME, KEY_HOME_SHIFTED, KEY_DELETE,
	KEY_ERASE, NEWLINE, KEY_COMPLETION, "\4", 0};
	i = 0;
	j = 0;
	while (specialchar[j])
	{
		i = ft_strprefix(specialchar[j], str);
		if (i)
			return (i);
		j++;
	}
	return (ft_lenchar_r(str, 0));
}
