/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:00:44 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/10 14:35:57 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_base(size_t nbr, char *base)
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
		ft_putchar_fd(base[((nbr / divisor) % b)], 1);
		divisor /= b;
	}
}