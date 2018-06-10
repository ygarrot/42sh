/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 14:13:36 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_read_recover(t_read *parser)
{
	char	*ret;

	if (!parser)
		return (0);
	if (parser->echo == 0)
	{
		ft_putstr_fd(parser->prompt, STDERR_FILENO);
		re = ft_read_recover_simple(parser);
	}
	else if (parser->readline_ative)
		ret = ft_read_recover_hard(parser);
	else
	{
		ft_putstr_fd(parser->prompt, STDERR_FILENO);
		ret = ft_read_recover_simple(parser);
	}
	return (ret);
}
