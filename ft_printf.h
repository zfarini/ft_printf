#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include "libft.h"

#ifndef FT_PRINTF_H
#define FT_PRINTF_H


typedef struct s_ft_printf_info {
	
	int left_justify;
	int force_sign;
	int force_space;
	int hash;
	int padding_with_0;
	int min_width;
	int precision_width;
	int precision_set;

	int is_hex;
	int width;
	char sp;
	int i_value;
	int bytes_written;
	int write_failed;
	size_t u_value;

}	t_ft_printf_info;

int ft_printf(const char *format, ...);
int	ft_putnbr_base(size_t nbr, char *base);
#endif