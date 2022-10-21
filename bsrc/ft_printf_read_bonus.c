/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:30:32 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 12:01:23 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	read_precision(const char **fmt, t_printf_info *info)
{
	info->precision = -1;
	if (**fmt == '.')
	{
		*fmt = *fmt + 1;
		info->precision = 0;
		while (ft_isdigit(**fmt))
		{
			info->precision = info->precision * 10 + (**fmt - '0');
			*fmt = *fmt + 1;
		}
	}
}

const char	*read_format_specifier(const char *fmt, t_printf_info *info)
{
	if (*fmt != '%')
		return (fmt);
	while (str_find("+- #0", *(++fmt)))
	{
		if (*fmt == '+')
			info->plus = 1;
		else if (*fmt == '-')
			info->minus = 1;
		else if (*fmt == ' ')
			info->space = 1;
		else if (*fmt == '#')
			info->hash = 1;
		else if (*fmt == '0')
			info->zero = 1;
	}
	while (ft_isdigit(*fmt))
		info->min_width = info->min_width * 10 + (*(fmt++) - '0');
	read_precision(&fmt, info);
	info->sp = *fmt;
	if (info->precision >= 0 || info->minus)
		info->zero = 0;
	if (*fmt)
		fmt++;
	return (fmt);
}
