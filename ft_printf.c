#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include "libft.h"


#define FLAGS_SIZE 256

void add_flags(int *flags, char *format, int *i)
{
	ft_memset(flags, 0, FLAGS_SIZE * sizeof(int));
	while (ft_strchr("-+ #0", format[*i]))
	{
		flags[format[*i]] = 1;
		*i++;
	}
	while (ft_isdigit(format[*i]))
		flags['w'] = flags['w'] * 10 + (format[*i++] - '0');
	if (format[*i] == '.')
	{
		*i++;
		while (ft_isdigit(format[*i]))
			flags['.'] = flags['.'] * 10 + (format[*i++] - '0');
	}
}

char *ft_utoa_hex(size_t n, int upper_case)
{

}

char *ft_utoa(unsigned int n)
{

}

char	*find_initial_s(va_list *pap, char c)
{
	va_list ap;
	va_copy(ap, *pap);
	char *res = 0;

	if (c == 'd' || c == 'i')
		res = ft_itoa(va_arg(ap, int));
	else if (c == 'u')
		res = ft_utoa(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		res = ft_utoa_hex(va_arg(ap, unsigned int), c == 'X');
	else if (c == 'p')
		res = ft_utoa_hex(va_arg(ap, size_t), 0);
	else if (c == 's')
		res = ft_strdup(va_arg(ap, char *));
	else if (c == 'c' || c == '%')
	{
		res = calloc(2, sizeof(char));
		if (res)
			res[0] = c;
	}
	va_end(ap);
	return (res);
}

void insert_str_at(char **s, int i, char *s2)
{

}

char	*update_s_using_flags(int *flags, char *s, char c)
{
	
	if (ft_strchr("id", c) && ft_isdigit(s[0]))
	{
		if (flags['+'])
			insert_str_at(&s, 0, "+");
		else if (flags[' '])
			insert_str_at(&s, 0, " ");
	}
	if (flags['#'] && ft_strchr("xX", c))
	{
		if (c == 'x')
			insert_str_at(&s, 0, "0x");
		else
			insert_str_at(&s, 0, "0X");
	}
	if (c == 'p')
		insert_str_at(&s, 0, "0x");
	int len = ft_strlen(s);
	int j;
	if (len < flags['w'])
	{
		j = -1;
		if (flags['-'])
		{
			//TODO: this is dump just realloc, memset to spaces and then copy
			while (++j < flags['w'] - len)
				insert_str_at(&s, ft_strlen(s), " ");
		}
		else
		{
			if (flags['0'])
			{
				if (ft_strchr("iduxXp", c))
				{
					int at = !ft_isdigit(s[0]);
					if (!ft_isdigit(s[1]))
						at = 2;
					j = -1;
					while (++j < flags['w'] - len)
						insert_str_at(&s, at, "0");
				}
				//todo: what about "sc%"?
			}
			else
			{
				j = -1;
				while (++j < flags['w'] - len)
					insert_str_at(&s, 0, " ");
			}
		}
	}
}

int ft_printf(char *format, ...)
{
	int flags[FLAGS_SIZE];
	va_list	ap;
	va_start(ap, format);
	int bytes_written = 0;
	int i = 0;//TODO: remove this and use just format
	while (format[i])
	{
		if (format[i] == '%')
		{
			add_flags(flags, format, &i);
			if (!ft_strchr("cspdiuxX%", format[i]))//todo: are u sure we should continue?
				continue;
			char	*s = find_initial_s(&ap, format[i]);
			s = update_s_using_flags(flags, s, format[i]);
			bytes_written = write(1, s, ft_strlen(s));//TODO: write fail
			//!!TODO: should we va_arg() here?
			i++;
		}
		else
		{
			bytes_written += write(1, &format[i], 1); // TODO: write fail
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
	printf("%010s", "tt");
	
}