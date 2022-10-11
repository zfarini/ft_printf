/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:44:40 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/11 14:23:27 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print(t_ft_printf_info *info, char *s, int cnt)
{
	int	b;

	b = write(1, s, cnt);
	if (b < 0)
		info->write_failed = 1;
	info->bytes_written += b;
}

int	int_len(int n)
{
	int	res;

	res = (n == 0);
	while (n)
	{
		res++;
		n /= 10;
	}
	return (res);
}

int	uint_len(size_t n, int hex)
{
	int	res;

	res = (n == 0);
	while (n)
	{
		res++;
		if (hex)
			n /= 16;
		else
			n /= 10;
	}
	return (res);
}

void	find_value_width(t_ft_printf_info *info)
{
	if (ft_strchr("id", info->sp))
		info->width += int_len(info->i_value);
	else if (ft_strchr("xXup", info->sp))
		info->width += uint_len(info->u_value, info->is_hex);
	else if (info->sp == 's')
	{
		if (info->precision_set
			&& ft_strlen((char *)info->u_value) > (size_t)info->precision_width)
			info->width += info->precision_width;
		else
			info->width += ft_strlen((char *)info->u_value);
	}
	else if (info->sp == 'c')
		info->width++;
	else
		assert(0);
}

void	find_width(t_ft_printf_info *info)
{
	find_value_width(info);
	if (info->precision_width > info->width)
		info->width = info->precision_width;
	if (ft_strchr("id", info->sp)
		&& (info->force_sign
			|| info->force_space
			|| info->i_value < 0))
		info->width++;
	if (info->is_hex
		&& (info->sp == 'p' || info->hash)
		&& (info->u_value || info->sp == 'p'))
		info->width += 2;
}

void	add_point_flag(const char **fmt, t_ft_printf_info *info)
{
	if (**fmt == '.')
	{
		info->precision_set = 1;
		*fmt = *fmt + 1;
		while (ft_isdigit(**fmt))
		{
			info->precision_width = info->precision_width * 10 + (**fmt - '0');
			*fmt = *fmt + 1;
		}
	}
}

void	add_flags(const char **fmt, t_ft_printf_info *info)
{
	while (ft_strchr("+- #0", **fmt))
	{
		if (**fmt == '+')
			info->force_sign = 1;
		else if (**fmt == '-')
			info->left_justify = 1;
		else if (**fmt == ' ')
			info->force_space = 1;
		else if (**fmt == '#')
			info->hash = 1;
		else if (**fmt == '0')
			info->padding_with_0 = 1;
		*fmt = *fmt + 1;
	}
	while (ft_isdigit(**fmt))
	{
		info->min_width = info->min_width * 10 + (**fmt - '0');
		*fmt = *fmt + 1;
	}
	add_point_flag(fmt, info);
}

/*!TODO: make sure we can pass ap as value*/
void	read_value_and_find_width(va_list ap, char c, t_ft_printf_info *info)
{
	info->sp = c;
	if (ft_strchr("id", c))
		info->i_value = va_arg(ap, int);
	else if (ft_strchr("xXu", c))
		info->u_value = va_arg(ap, unsigned int);
	else if (c == 'p')
		info->u_value = (size_t)va_arg(ap, void *);
	else if (c == 's')
	{
		info->u_value = (size_t)va_arg(ap, char *);
		if (!info->u_value)
			info->u_value = (size_t)"(null)";
	}
	else if (c == 'c')
		info->i_value = va_arg(ap, int);
	if (ft_strchr("xXp", c))
		info->is_hex = 1;
	find_width(info);
}

void	print_sign(t_ft_printf_info *info)
{
	if (info->i_value < 0)
		print(info, "-", 1);
	else if (info->force_sign)
		print(info, "+", 1);
	else if (info->force_space)
		print(info, " ", 1);
}

/*TODO: check this again */
void	print_min_width(t_ft_printf_info *info)
{
	int	w;

	w = info->min_width - info->width;
	while (w > 0)
	{
		if (!info->precision_set && info->padding_with_0)
			print(info, "0", 1);
		else
			print(info, " ", 1);
		w--;
	}
}

void	print_0x(t_ft_printf_info *info)
{
	if (info->sp == 'p' || (info->sp == 'x' && info->hash && info->u_value))
		print(info, "0x", 2);
	if (info->hash && info->sp == 'X' && info->u_value)
		print(info, "0X", 2);
}

void	putnbr(t_ft_printf_info *info, int n)
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

void	print_missing_zeroes(t_ft_printf_info *info)
{
	int	w;

	if (ft_strchr("id", info->sp))
	{
		w = info->precision_width - int_len(info->i_value);
		while (w > 0)
		{
			print(info, "0", 1);
			w--;
		}
		putnbr(info, info->i_value);
	}
	if (ft_strchr("xXu", info->sp))
	{
		w = info->precision_width - uint_len(info->u_value, info->sp != 'u');
		while (w > 0)
		{
			print(info, "0", 1);
			w--;
		}
	}
}

void	putnbr_base(t_ft_printf_info *info, size_t nbr, char *base)
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

void	print_the_actual_object(t_ft_printf_info *info)
{
	int	i;
	int	l;

	if (info->sp == 'u')
		putnbr_base(info, info->u_value, "0123456789");
	else if (ft_strchr("xp", info->sp))
		putnbr_base(info, info->u_value, "0123456789abcdef");
	else if (info->sp == 'X')
		putnbr_base(info, info->u_value, "0123456789ABCDEF");
	else if (info->sp == 's')
	{
		l = ft_strlen((char *)info->u_value);
		if (info->precision_set && l > info->precision_width)
			l = info->precision_width;
		i = 0;
		while (i < l)
			print(info, ((char *)info->u_value) + i++, 1);
	}
	else if (info->sp == 'c')
		print(info, (char *)&info->i_value, 1);
}

/*!!!TODO: handle the case when precision_width = 0 and we should print 0*/
/*!TODO: should we return when we find an anvalid char?*/
int	print_format(const char **fmt, va_list ap)
{
	t_ft_printf_info	info;

	ft_memset(&info, 0, sizeof(info));
	add_flags(fmt, &info);
	if (!ft_strchr("cspdiuxX%", **fmt))
		return (0);
	if (**fmt == '%')
		return (write(1, (*fmt)++, 1));
	read_value_and_find_width(ap, **fmt, &info);
	if (!info.precision_set && info.padding_with_0 && ft_strchr("id", info.sp))
		print_sign(&info);
	if (!info.left_justify)
		print_min_width(&info);
	if (ft_strchr("id", info.sp)
		&& (info.precision_set || !info.padding_with_0))
		print_sign(&info);
	print_0x(&info);
	print_missing_zeroes(&info);
	print_the_actual_object(&info);
	if (info.left_justify)
		print_min_width(&info);
	if (info.write_failed)
		info.bytes_written = -1;
	*fmt = *fmt + 1;
	return (info.bytes_written);
}

int	ft_printf(const char *fmt, ...)
{
	va_list				ap;
	int					bytes_written;
	int					b;

	va_start(ap, fmt);
	bytes_written = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			b = print_format(&fmt, ap);
		}
		else
		{
			b = write(1, fmt, 1);
			fmt++;
		}
		if (b < 0)
			return (-1);
		bytes_written += b;
	}
	va_end(ap);
	return (bytes_written);
}
