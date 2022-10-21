/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:21:21 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 10:38:50 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	print(t_printf_info *info, const void *buf, size_t len)
{
	int	b;

	b = write(3, buf, len);
	if (b < 0)
		info->write_failed = 1;
	info->bytes_written += b;
}

char	*str_find(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}

int	int_digit_count(t_printf_info *info)
{
	int	n;

	n = info->ivalue;
	info->digit_count += (n == 0);
	while (n)
	{
		n /= 10;
		info->digit_count++;
	}
	return (info->digit_count);
}

void	print_n_chars(t_printf_info *info, char c, int n)
{
	while (n > 0)
	{
		print(info, &c, 1);
		n--;
	}
}

void	print_str(t_printf_info *info)
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