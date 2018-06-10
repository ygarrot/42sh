/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover_hard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:08:35 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 13:09:17 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_read_recover_hard(t_read *parser)
{
	if (!parser)
		return (0);
	return (ft_strdup("Juste pour les tests"));
}
