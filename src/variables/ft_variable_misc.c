/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_misc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 11:48:51 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/03 14:40:52 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	ft_variablecmp(void *left, void *right)
{
	if (!left || !right)
		return (0);
	return (ft_strcmp(((t_variable*)left)->name, ((t_variable*)right)->name));
}
