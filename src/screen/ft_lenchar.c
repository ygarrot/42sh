/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:05:15 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 13:26:19 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_lenchar_l(char *str, int pos)
{
	int	i;

	if (pos == 0 || !str)
		return (0);
	i = 1;
	while (pos - i >= 0 && (str[pos - i] & '\xc0') == '\x80')
		i++;
	return (i);
}

int		ft_lenchar_r(char *str, int pos)
{
	int	i;

	if (!str || !str[pos])
		return (0);
	i = 1;
	while (str[pos + i] && (str[pos + i] & '\xc0') == '\x80')
		i++;
	return (i);
}

int		ft_lennchar_l(char *str, int pos, int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i += ft_lenchar_l(str, pos - i);
		n--;
	}
	return (i);
}

int		ft_lennchar_r(char *str, int pos, int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i += ft_lenchar_r(str, pos + i);
		n--;
	}
	return (i);
}
