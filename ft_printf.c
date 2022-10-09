#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include "libft.h"


int ft_printf(char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	printf("%d\n", va_arg(ap, int));
	va_end(ap);
}	

int main()
{
	int x = 42;
	//printf("%");
	#define T(fmt, ...) printf(fmt"\n", __VA_ARGS__), fflush(stdout), ft_printf(fmt"\n", __VA_ARGS__)
	//T("%s%c%%%d%c%i", "hello", 'a', -42, '!', -(1 << 31));
	printf("'% d't\n", 42);
	ft_printf("", 3);
}