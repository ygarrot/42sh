/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parserpushback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 12:34:36 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/18 12:36:39 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_parserpushback(t_parser *parser, t_parser *end)
{
	if (!parser)
		return ;
	while (parser->next)
		parser = parser->next;
	parser->next = end;
}
