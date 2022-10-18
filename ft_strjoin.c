/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:48:48 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/13 18:37:46 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = ft_calloc(size, 1);
	if (!res)
		return (0);
	ft_strlcat(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}
