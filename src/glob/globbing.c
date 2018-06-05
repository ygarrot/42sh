/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:50:42 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/26 15:35:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		brace(char **str, char **match)
{
	int		i;
	int		len;
	int		temp;

	i = 1;
	if (**match != '{' || ft_charchr('}', &(*match)[1]) < 0)
		return (0);
	len = ft_strlento_comm(*match, "}");
	while (match[0][i - 1] != '}')
	{
		temp = ft_strlento_comm(&match[0][i], ",}");
		if (!ft_strncmp(*str, &match[0][i], temp - 1))
		{
			*str += temp - 1;
			*match += len;
			return (1);
		}
		i += temp;
	}
	return (0);
}

char	*enclosed(char *str, char c)
{
	int		i;
	int		len;
	int		inv;

	if (!str || !ft_isin(*str, "[?"))
		return (NULL);
	if (*str == '?')
		return (str + 1);
	str++;
	inv = (*str == '^' && str++) ? 1 : 0;
	i = 0;
	len = ft_strlento_comm(str, "]");
	while (i - len)
	{
		(str[i] == '\\') ? i++ : 0;
		if (len - i + 2 >= 0 && str[i + 1] == '-')
		{
			if (c >= str[i] && c <= str[i + 2])
				return (inv ? NULL : &str[len]);
			i += 2;
		}
		if (c == str[i++])
			return (inv ? NULL : &str[len]);
	}
	return (inv ? &str[len] : NULL);
}

int		is_special(char **str, char **to_match)
{
	char	*temp;
	int		i;

	i = 0;
	if (**to_match == '{')
		return (brace(str, to_match));
	if ((temp = enclosed(*to_match, **str)))
	{
		*to_match = temp;
		++*str;
	}
	if (temp || **to_match == '[')
		return (temp ? 1 : 0);
	while (to_match[0][i] && !ft_isin(to_match[0][i], GLOB)
			&& to_match[0][i] == str[0][i])
		i++;
	if ((to_match[0][i] && !ft_isin(to_match[0][i], GLOB))
			|| (!to_match[0][i] && str[0][i]))
		return (0);
	*to_match = &to_match[0][i];
	*str = &str[0][i];
	return (i | 1);
}

int		ft_match(char *str, char *to_match)
{
	if (!to_match || !str)
		return (0);
	if (!*str && !*to_match)
		return (1);
	else if (!*str)
		return (*to_match == '*' ? ft_match(str, to_match + 1) : 0);
	if (*to_match == '*')
	{
		if (ft_match(str, to_match + 1))
			return (1);
		return (ft_match(str + 1, to_match));
	}
	else if (is_special(&str, &to_match))
		return (ft_match(str, to_match));
	return (0);
}
