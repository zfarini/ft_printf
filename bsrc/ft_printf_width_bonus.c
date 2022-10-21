/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_width_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:24:19 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 12:02:38 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	find_the_value_width(t_printf_info *info)
{
	if (str_find("id", info->sp))
		info->width += int_digit_count(info);
	else if (str_find("xXu", info->sp))
		info->width += uint_digit_count(info);
	else if (info->sp == 'p')
		info->width += ptr_digit_count(info);
	else if (info->sp == 's')
	{
		if (!info->ptr)
			info->ptr = "(null)";
		if (info->precision >= 0)
		{
			while (info->width < info->precision
				&& ((char *)info->ptr)[info->width])
				info->width++;
		}
		else
			info->width += ft_strlen((char *)info->ptr);
	}
	else if (info->sp == 'c' || info->sp == '%')
		info->width++;
}

void	find_the_formatted_value_width(t_printf_info *info)
{
	find_the_value_width(info);
	if (str_find("idxXu", info->sp) && info->precision > info->width)
		info->width = info->precision;
	if (str_find("idxXu", info->sp) && !info->precision
		&& !info->ivalue && !info->uvalue)
		info->width--;
	if (str_find("id", info->sp)
		&& (info->plus || info->space || info->ivalue < 0))
		info->width++;
	if (info->sp == 'p' || (info->hash && info->uvalue))
		info->width += 2;
}
