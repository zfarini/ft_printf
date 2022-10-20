/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:24:11 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/20 21:37:28 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	TODO: ft_strchr also checks for '\0' (fow now I changed it)
*/

void	print(t_printf_info *info, const void *buf, size_t len)
{
	int	b;

	b = write(3, buf, len);
	if (b < 0)
		info->write_failed = 1;
	info->bytes_written += b;
}

void	print_int(t_printf_info *info, int n)
{
	int		p;
	int		x;
	char	c;

	p = 1;
	x = n;
	while (x >= 10 || x <= -10)
	{
		x /= 10;
		p *= 10;
	}
	while (p > 0)
	{
		if (n < 0)
			c = -((n / p) % 10) + '0';
		else
			c = (n / p) % 10 + '0';
		p /= 10;
		print(info, &c, 1);
	}
}

void	print_uint_base(t_printf_info *info, size_t nbr, char *base)
{
	size_t	divisor;
	size_t	nb_copy;
	size_t	b;

	b = ft_strlen(base);
	divisor = 1;
	nb_copy = nbr;
	while (nb_copy >= b)
	{
		divisor *= b;
		nb_copy /= b;
	}
	while (divisor > 0)
	{
		print(info, &base[((nbr / divisor) % b)], 1);
		divisor /= b;
	}
}

void	print_ptr(t_printf_info *info, uintptr_t p)
{
	uintptr_t	divisor;
	uintptr_t	tmp;

	divisor = 1;
	tmp = p;
	while (tmp >= 16)
	{
		divisor *= 16;
		tmp /= 16;
	}
	while (divisor > 0)
	{
		print(info, &"0123456789abcdef"[(p / divisor) % 16], 1);
		divisor /= 16;
	}
}

void read_precision(const char **fmt, t_printf_info *info)
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

void read_format_specifier(const char **fmt, t_printf_info *info)
{
	while (ft_strchr("+- #0", **fmt))
	{
		if (**fmt == '+')
			info->plus = 1;
		else if (**fmt == '-')
			info->minus = 1;
		else if (**fmt == ' ')
			info->space = 1;
		else if (**fmt == '#')
			info->hash = 1;
		else if (**fmt == '0')
			info->zero = 1;
		*fmt = *fmt + 1;
	}
	while (ft_isdigit(**fmt))
	{
		info->min_width = info->min_width * 10 + (**fmt - '0');
		*fmt = *fmt + 1;
	}
	read_precision(fmt, info);
	info->sp = **fmt;
	if (**fmt)
		*fmt = *fmt + 1;
}

int	int_digit_count(t_printf_info *info)
{
	int	res;
	int n;

	n = info->ivalue;
	res = (n == 0);
	info->digit_count += (n == 0);
	while (n)
	{
		res++;
		n /= 10;
		info->digit_count++;
	}
	return (res);
}

int	uint_digit_count(t_printf_info *info)
{
	int	res;
	size_t  n;

	n = info->uvalue;
	res = (n == 0);
	info->digit_count = (n == 0);
	while (n)
	{
		res++;
		if (ft_strchr("pxX", info->sp))
			n /= 16;
		else
			n /= 10;
		info->digit_count++;
	}
	return (res);
}

int ptr_digit_count(t_printf_info *info)
{
	int			res;
	uintptr_t 	n;

	n = (uintptr_t)info->ptr;
	res = (n == 0);
	info->digit_count = (n == 0);
	while (n)
	{
		res++;
		n /= 16;
		info->digit_count++;
	}
	return (res);
}

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
			while (info->width < info->precision && ((char *)info->ptr)[info->width])
				info->width++;
		}
		else
			info->width += ft_strlen((char *)info->ptr);
	}
	else if (info->sp == 'c')
		info->width++;
}

void find_the_formatted_value_width(t_printf_info *info)
{
	find_the_value_width(info);
	if (ft_strchr("idxXup", info->sp) && info->precision > info->width)
		info->width = info->precision;
	if (ft_strchr("idxXu", info->sp) && !info->precision && !info->ivalue && !info->uvalue)
		info->width--;
	if (ft_strchr("id", info->sp) && (info->plus || info->space || info->ivalue < 0))
		info->width++;
	if (info->sp == 'p' || (info->hash && info->uvalue))
		info->width += 2;
}

void print_str(t_printf_info *info)
{
	int	l;

	if (info->precision >= 0)
	{
		l = 0;
		while (l < info->precision && ((char *)info->ptr)[l])
			l++;
	}
	else
		l = ft_strlen((char *)info->ptr);
	print(info, (char *)info->ptr, l);
}

void print_the_value(t_printf_info *info)
{
	if (ft_strchr("idxXu", info->sp) && !info->ivalue &&
		!info->uvalue && !info->precision)
		return ;
	if (ft_strchr("id", info->sp))
		print_int(info, info->ivalue);
	else if (info->sp == 'u')
		print_uint_base(info, info->uvalue, "0123456789");
	else if (info->sp == 'x')
		print_uint_base(info, info->uvalue, "0123456789abcdef");
	else if (info->sp == 'X')
		print_uint_base(info, info->uvalue, "0123456789ABCDEF");
	else if (info->sp == 'p')
		print_ptr(info, (uintptr_t)info->ptr);
	else if (info->sp == 's')
		print_str(info);
	else if (info->sp == 'c')
	{
		unsigned char c = info->ivalue;
		print(info, &c, 1);
	}
	else if (info->sp == '%')
		print(info, "%", 1);
}

void	print_n_chars(t_printf_info *info, char c, int n)
{

	while (n > 0)
	{
		print(info, &c, 1);
		n--;
	}
}

void	print_sign(t_printf_info *info)
{
	if (ft_strchr("id", info->sp))
	{
		if (info->ivalue < 0)
			print(info, "-", 1);
		else if (info->plus)
			print(info, "+", 1);
		else if (info->space)
			print(info, " ", 1);
	}
}

void	print_0x(t_printf_info *info)
{
	if (info->sp == 'p' || (info->hash && info->uvalue))
	{
		if (info->sp == 'X')
			print(info, "0X", 2);
		else
			print(info, "0x", 2);
	}
}

void print_the_formatted_value(t_printf_info *info)
{
	find_the_formatted_value_width(info);
	if (info->precision >= 0 || info->minus)
		info->zero = 0;
	if (!info->zero && !info->minus)
		print_n_chars(info, ' ', info->min_width - info->width);
	print_sign(info);
	print_0x(info);
	if (info->zero)
		print_n_chars(info, '0', info->min_width - info->width);
	if (ft_strchr("xXidu", info->sp))
		print_n_chars(info, '0', info->precision - info->digit_count);
	print_the_value(info);
	if (info->minus)
		print_n_chars(info, ' ', info->min_width - info->width);
}

int	ft_vprintf(const char *fmt, va_list ap)
{
	t_printf_info	info;
	int				bytes_written;

	bytes_written = 0;
	while (*fmt)
	{
		ft_bzero(&info, sizeof(info));
		if (*fmt != '%')
			print(&info, fmt++, 1);
		else
		{
			fmt++;
			read_format_specifier(&fmt, &info);
			if (ft_strchr("idc", info.sp))
				info.ivalue = va_arg(ap, int);
			else if (ft_strchr("xXu", info.sp))
				info.uvalue = va_arg(ap, unsigned int);
			else if (info.sp == 's')
				info.ptr = va_arg(ap, const char *);
			else if (info.sp == 'p')
				info.ptr = va_arg(ap, void *);
			print_the_formatted_value(&info);
		}
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
