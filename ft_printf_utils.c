/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:21:21 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/20 22:55:06 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_digit_count(t_printf_info *info)
{
	int	res;
	int	n;

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
	int		res;
	size_t	n;

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

int	ptr_digit_count(t_printf_info *info)
{
	int			res;
	uintptr_t	n;

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

void	print_n_chars(t_printf_info *info, char c, int n)
{
	while (n > 0)
	{
		print(info, &c, 1);
		n--;
	}
}

/*TODO: shouldn't be here*/
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
