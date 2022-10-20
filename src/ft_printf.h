/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:43:10 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/20 22:15:10 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdarg.h>
# include "libft.h"
# include <assert.h>

typedef struct s_printf_info {
    char sp;
    int plus;
    int minus;
    int hash;
    int zero;
    int space;
    int width;
    int min_width; // should this be int?
    int precision; // same as above
    int ivalue;
    int digit_count;
    int write_failed;
    int bytes_written;
    unsigned int  uvalue;
	const void	*ptr;
}   t_printf_info;

int ft_printf(const char *fmt, ...);
//int	ft_vprintf(const char *fmt, int *bytes_written, va_list ap);

int ft_vprintf(const char *fmt, va_list ap);

#endif