/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <zfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:43:10 by zfarini           #+#    #+#             */
/*   Updated: 2022/10/21 09:45:22 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft/libft.h"

# define BASE_10 "0123456789"
# define BASE_16_LOWERCASE "0123456789abcdef"
# define BASE_16_UPPERCASE "0123456789ABCDEF"

typedef struct s_printf_info {
	char			sp;
	int				plus;
	int				minus;
	int				hash;
	int				zero;
	int				space;
	int				min_width;
	int				precision;
	int				width;
	int				digit_count;
	int				write_failed;
	int				bytes_written;
	int				ivalue;
	unsigned int	uvalue;
	const void		*ptr;
}			t_printf_info;

char		*str_find(const char *s, char c);
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
