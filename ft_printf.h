#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include "libft.h"

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
typedef union  value_s {
	int	i;
	size_t u;
} value_t;

typedef enum type_e {
	TYPE_INT,
	TYPE_UINT,
	TYPE_STR,
	TYPE_CHAR,
	TYPE_PTR
} type_t;

typedef struct ft_printf_info_s {
	int left_justify;
	int force_sign;
	int force_space;
	int hash;
	int padding_with_0;
	int min_width;
	int precision_width;
	int precision_set;
	int is_hex; // 1 for lower case hex and 2 for upper
	int width;
	char sp;
	type_t type;
	int i_value;
	size_t u_value;

}	ft_printf_info_t;

int ft_printf(const char *format, ...);
int	ft_putnbr_base(size_t nbr, char *base);
#endif