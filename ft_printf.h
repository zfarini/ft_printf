/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:43:10 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/20 22:54:23 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdarg.h>
# include "../libft/libft.h"
# include <assert.h>

typedef struct s_printf_info {
	char			sp;
	int				plus;
	int				minus;
	int				hash;
	int				zero;
	int				space;
	int				width;
	int				min_width;
	int				precision;
	int				ivalue;
	int				digit_count;
	int				write_failed;
	int				bytes_written;
	unsigned int	uvalue;
	const void		*ptr;
}			t_printf_info;

int			int_digit_count(t_printf_info *info);
int			uint_digit_count(t_printf_info *info);
int			ptr_digit_count(t_printf_info *info);
void		print_n_chars(t_printf_info *info, char c, int n);
void		print_str(t_printf_info *info);
void		print_int(t_printf_info *info, int n);
void		print_uint_base(t_printf_info *info, size_t nbr, char *base);
void		print_ptr(t_printf_info *info, uintptr_t p);
const char	*read_format_specifier(const char *fmt, t_printf_info *info);
void		find_the_formatted_value_width(t_printf_info *info);
void		print(t_printf_info *info, const void *buf, size_t len);
int			ft_printf(const char *fmt, ...);
int			ft_vprintf(const char *fmt, va_list ap);

#endif