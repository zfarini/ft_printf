/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:25:07 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/11 08:35:51 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	p;
	int	x;
	int r;

	r = 0;
	p = 1;
	x = n;
	while (x >= 10 || x <= -10)
	{
		x /= 10;
		p *= 10;
	}
	if (n < 0)
		r += ft_putchar_fd('-', fd);
	while (p > 0)
	{
		if (n < 0)
			r += ft_putchar_fd(-((n / p) % 10) + '0', fd);
		else
			r += ft_putchar_fd((n / p) % 10 + '0', fd);
		p /= 10;
	}
	return (r);
}
