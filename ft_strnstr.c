/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:42:29 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/06 19:08:36 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	int		flag;

	if (!needle[0] && !haystack[0])
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		flag = 0;
		while (needle[j] && haystack[i + j] && i + j < len)
		{
			if (needle[j] != haystack[i + j])
				flag = 1;
			j++;
		}
		if (!flag && !needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
