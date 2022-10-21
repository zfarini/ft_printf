/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:23:07 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 10:38:42 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

int	uint_digit_count(t_printf_info *info)
{
	size_t	n;

	n = info->uvalue;
	info->digit_count = (n == 0);
	while (n)
	{
		if (str_find("pxX", info->sp))
			n /= 16;
		else
			n /= 10;
		info->digit_count++;
	}
	return (info->digit_count);
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

int	ptr_digit_count(t_printf_info *info)
{
	uintptr_t	n;

	n = (uintptr_t)info->ptr;
	info->digit_count = (n == 0);
	while (n)
	{
		n /= 16;
		info->digit_count++;
	}
	return (info->digit_count);
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
		print(info, &BASE_16_LOWERCASE[(p / divisor) % 16], 1);
		divisor /= 16;
	}
}
