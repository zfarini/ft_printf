#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include "libft.h"


int ft_putchar(char c)
{
	return (write(1, &c ,1));
}

//note: these are specific to printf 
char	*ft_itoa_base(int n, char *base)
{
	return 0;
}

char	*ft_utoa_base(size_t n, char *base)
{
	return 0;
}

int ft_printf(char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	int bytes_written = 0;
	int i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			int flags[256];
			ft_memset(flags, 0, sizeof(flags));

			
			int left_justify = 0;
			int force_sign = 0;
			int force_space = 0;
			int hash = 0;
			int padding_with_0 = 0;
			int min_width = 0;
			int min_digits = 0;

			char c = format[i];

			while (ft_strchr("-+ #0", c))
			{
				flags[c] = 1;
			}
			if (format[i] == '-')
				left_justify = 1;
			else if (format[i] == '+')
				force_sign = 1;
			else if (format[i] == ' ')
				force_space = 1;
			else if (format[i] == '#')
				hash = 1;
			else if (format[i] == '0')
				padding_with_0 = 1;
			else if (!format[i])
			{
				break;
			}
			else
				i--;
			i++;
			//check for width
			if (ft_isdigit(format[i]))
			{
				while (ft_isdigit(format[i]))
				{
					min_width = min_width * 10 + (format[i] - '0');
					i++;
				}
			}
			//TODO: what if we have width padding and this?
			if (format[i] == '.')
			{
				i++;
				//TODO: what if the first one is not a digit
				while (ft_isdigit(format[i]))
				{
					min_digits = min_digits * 10 + (format[i] - '0');
					i++;
				}
			}
			//cspdiuxX%
			if (!ft_strchr("cspdiuxX%", format[i]))
				continue;
			//let's first of all save the result to a str
			char *s = 0;//
			if (format[i] == 'd' || format[i] == 'i')
				s = ft_itoa_base(va_arg(ap, int), "0123456789");
			else if (format[i] == 'c' || format[i] == '%')//todo: make sure these work the same
			{
				s = ft_calloc(2, sizeof(char));
				s[0] = va_arg(ap, int);
			}
			else if (format[i] == 's')
			{
				char *s2 = va_arg(ap, char *);
				if (!s2)
					s2 = "(null)";
				s = ft_strdup(s2);
			}
			else if (format[i] == 'p')
				s = ft_utoa_base(va_arg(ap, size_t), "012345679abcdef");
			else if (format[i] == 'u')
				s = ft_utoa_base(va_arg(ap, unsigned int), "0123456789");
			else if (format[i] == 'x')
				s = ft_utoa_base(va_arg(ap, unsigned int), "012345679abcdef");
			else if (format[i] == 'X')
				s = ft_utoa_base(va_arg(ap, unsigned int), "012345679ABCDEF");
			else
				assert(0);
			size_t len = ft_strlen(s);
			if (ft_strchr("id", format[i]) && s[0] != '-')
			{
				char *s2;
				if (force_sign)
					s2 = ft_strjoin("+", s);
				else if (force_space)
					s2 = ft_strjoin(" ", s);
				free(s2);
				s = s2;
			}
			if (ft_strchr("piduxX", format[i]))
			{
				int has_sign = !ft_isdigit(s[0]);
				int digit_cnt = ft_strlen(s) - has_sign;
				if (digit_cnt < min_digits)
				{
					char *s2 = malloc(min_digits + has_sign + 1);
					if (has_sign)
						s2[0] = s[0];
					for (int k = has_sign; k < min_digits - digit_cnt + has_sign; k++)
						s2[k] = '0';
					//todo: fix this
					char *s3 = ft_strjoin(s2, s + has_sign);
					free(s);
					free(s2);
					s = s3;
				}
			}
			//todo: compress these
			if (hash && ft_strchr("xX", format[i]))
			{
				char *s2;
				if (format[i] == 'x')
					s = ft_strjoin("0x", s);
				else
					s = ft_strjoin("0X", s);
				free(s);
				s = s2;
			}
			
			//if (format[i] == 'd' || format[i])
			if (!left_justify && len < min_width)
			{
				int j = 0;
				while (j < min_width - len)
				{
					if (padding_with_0)
						ft_putchar('0');
					else
						ft_putchar(' ');
					j++;
				}
			}

			i++;
		}
		else
		{
			if (ft_putchar(format[i]) < 0)
				return (-1);
			bytes_written++;
			i++;
		}
	}
	va_end(ap);
}	

int main()
{
	int x = 42;
	//printf("%");
	#define T(fmt, ...) printf(fmt"\n", __VA_ARGS__), fflush(stdout), ft_printf(fmt"\n", __VA_ARGS__)
	//T("%s%c%%%d%c%i", "hello", 'a', -42, '!', -(1 << 31));
	void *ptr = 42;
	printf("%+04d\n", ptr);
	
}