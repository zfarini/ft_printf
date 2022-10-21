/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:44:09 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 12:01:31 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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