/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooseconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:34:09 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/19 15:49:55 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*chooseconv(va_list va, t_arg *list)
{
	if (list->conv == 14)
		return ("%");
	if (list->conv == 6)
		return (convuimx((unsigned long)va_arg(va, void*)));
	if (list->conv == 10 && list->specifier != 3)
		return (convc((int)va_arg(va, void*)));
	if (list->conv == 11 || list->conv == 10)
		return (convwchar((wchar_t)va_arg(va, void*)));
	if (list->conv == 12 && list->specifier != 3)
		return ((char*)va_arg(va, void*));
	if (list->conv == 13 || list->conv == 12)
		return (convwstr((wchar_t*)va_arg(va, void*)));
	if (list->conv > 6 && list->conv < 10)
		return (convsigned(va, list));
	return (convunsigned(va, list));
}

char	*convsigned(va_list va, t_arg *list)
{
	if (list->specifier == 3 || list->conv == 8)
		return (convim((long)va_arg(va, void*)));
	if (list->specifier == 0)
		return (convim((char)va_arg(va, void*)));
	if (list->specifier == 1)
		return (convim((short)va_arg(va, void*)));
	if (list->specifier == 2)
		return (convim((long long)va_arg(va, void*)));
	if (list->specifier == 4)
		return (convim((size_t)va_arg(va, void*)));
	if (list->specifier == 5)
		return (convim((intmax_t)va_arg(va, void*)));
	return (convim((int)va_arg(va, void*)));
}

char	*convunsigned(va_list va, t_arg *list)
{
	int			x;
	char		*(*um[3])(uintmax_t);

	um[0] = convuim;
	um[1] = convuimo;
	um[2] = convuimx;
	x = (list->conv == 5) ? 2 : 0;
	if (list->specifier == 3 || (list->conv > 2 && list->conv < 5))
	{
		return (um[list->conv > 2 ? list->conv - 3 : list->conv](
		(unsigned long)va_arg(va, void*)));
	}
	if (list->specifier == 0)
		return (um[x ? x : list->conv]((unsigned char)va_arg(va, void*)));
	if (list->specifier == 1)
		return (um[x ? x : list->conv]((unsigned short)va_arg(va, void*)));
	if (list->specifier == 2)
		return (um[x ? x : list->conv]((unsigned long long)va_arg(va, void*)));
	if (list->specifier == 4)
		return (um[x ? x : list->conv]((uintmax_t)va_arg(va, void*)));
	if (list->specifier == 5)
		return (um[x ? x : list->conv]((size_t)va_arg(va, void*)));
	return (um[x ? x : list->conv]((unsigned int)va_arg(va, void*)));
}
