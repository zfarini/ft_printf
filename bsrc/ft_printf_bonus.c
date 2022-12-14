/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:24:11 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 14:00:08 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	print_the_value(t_printf_info *info)
{
	unsigned char	c;

	if (str_find("idxXu", info->sp) && !info->ivalue
		&& !info->uvalue && !info->precision)
		return ;
	if (str_find("id", info->sp))
		print_int(info, info->ivalue);
	else if (info->sp == 'u')
		print_uint_base(info, info->uvalue, BASE_10);
	else if (info->sp == 'x')
		print_uint_base(info, info->uvalue, BASE_16_LOWERCASE);
	else if (info->sp == 'X')
		print_uint_base(info, info->uvalue, BASE_16_UPPERCASE);
	else if (info->sp == 'p')
		print_ptr(info, (uintptr_t)info->ptr);
	else if (info->sp == 's')
		print_str(info);
	else if (info->sp == 'c')
	{
		c = info->ivalue;
		print(info, &c, 1);
	}
	else if (info->sp == '%')
		print(info, "%", 1);
}

static void	print_the_formatted_value(t_printf_info *info)
{
	find_the_formatted_value_width(info);
	if (!info->zero && !info->minus)
		print_n_chars(info, ' ', info->min_width - info->width);
	if (str_find("id", info->sp))
	{
		if (info->ivalue < 0)
			print(info, "-", 1);
		else if (info->plus)
			print(info, "+", 1);
		else if (info->space)
			print(info, " ", 1);
	}
	if (info->sp == 'p' || (info->hash && info->uvalue && info->sp == 'x'))
		print(info, "0x", 2);
	if (info->hash && info->uvalue && info->sp == 'X')
		print(info, "0X", 2);
	if (info->zero)
		print_n_chars(info, '0', info->min_width - info->width);
	if (str_find("xXidu", info->sp))
		print_n_chars(info, '0', info->precision - info->digit_count);
	print_the_value(info);
	if (info->minus)
		print_n_chars(info, ' ', info->min_width - info->width);
}

static void	print_value(const char **fmt, t_printf_info *info)
{
	if (str_find("cspdiuxX%", info->sp))
		print_the_formatted_value(info);
	else if (**fmt && !info->sp)
	{
		print(info, *fmt, 1);
		*fmt = *fmt + 1;
	}
}

int	ft_vprintf(const char *fmt, va_list ap)
{
	t_printf_info	info;
	int				bytes_written;

	bytes_written = 0;
	while (*fmt)
	{
		ft_memset(&info, 0, sizeof(info));
		fmt = read_format_specifier(fmt, &info);
		if (str_find("idc", info.sp))
			info.ivalue = va_arg(ap, int);
		else if (str_find("xXu", info.sp))
			info.uvalue = va_arg(ap, unsigned int);
		else if (info.sp == 's')
			info.ptr = va_arg(ap, const char *);
		else if (info.sp == 'p')
			info.ptr = va_arg(ap, void *);
		print_value(&fmt, &info);
		if (info.write_failed)
			return (-1);
		bytes_written += info.bytes_written;
	}
	return (bytes_written);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		bytes_written;

	va_start(ap, fmt);
	bytes_written = ft_vprintf(fmt, ap);
	va_end(ap);
	return (bytes_written);
}
