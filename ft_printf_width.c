/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:24:19 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/20 22:30:45 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	find_the_value_width(t_printf_info *info)
{
	if (ft_strchr("id", info->sp))
		info->width += int_digit_count(info);
	else if (ft_strchr("xXu", info->sp))
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
	else if (info->sp == 'c')
		info->width++;
}

void	find_the_formatted_value_width(t_printf_info *info)
{
	find_the_value_width(info);
	if (ft_strchr("idxXup", info->sp) && info->precision > info->width)
		info->width = info->precision;
	if (ft_strchr("idxXu", info->sp) && !info->precision
		&& !info->ivalue && !info->uvalue)
		info->width--;
	if (ft_strchr("id", info->sp)
		&& (info->plus || info->space || info->ivalue < 0))
		info->width++;
	if (info->sp == 'p' || (info->hash && info->uvalue))
		info->width += 2;
}