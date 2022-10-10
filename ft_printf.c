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
		flags[(int)format[*i]] = 1;
		*i = *i + 1;
	}
	while (ft_isdigit(format[*i]))
	{
		flags['w'] = flags['w'] * 10 + (format[*i] - '0');
		*i = *i + 1;
	}
	if (format[*i] == '.')
	{
		*i = *i + 1;
		while (ft_isdigit(format[*i]))
			flags['.'] = flags['.'] * 10 + (format[*i++] - '0');
	}
}

int	ft_numlen_base(size_t n, int base)
{
	int	len;

	len = (n == 0);
	while (n)
	{
		len++;
		n /= base;
	}
	return (len);
}

char	*ft_utoa_hex(size_t n, int upper_case)
{
	int		i;
	char	*res;
		
	i = ft_numlen_base(n, 16);
	res = malloc(i + 1);
	if (!res)
		return (0);
	res[i--] = '\0';
	while (i >= 0)
	{
		if (upper_case)
			res[i--] = "0123456789ABCDEF"[n % 16];
		else
			res[i--] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	return (res);
}

char	*ft_utoa(unsigned int n)
{
	int		i;
	char	*res;
		
	i = ft_numlen_base(n, 10);
	res = malloc(i + 1);
	if (!res)
		return (0);
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i--] = n % 10;
		n /= 10;
	}
	return (res);
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
	else if (c == 'c')
	{
		res = calloc(2, sizeof(char));
		res[0] = va_arg(ap, int);
	}
	else if (c == '%')
	{
		res = calloc(2, sizeof(char));
		res[0] = '%';
	}
	va_end(ap);
	return (res);
}

void insert_str_at(char **s, int i, char *s2)
{
	char	*res;
	int		j;
	res = malloc(ft_strlen(*s) + ft_strlen(s2) + 1);
	j = 0;
	while (j < i)
	{
		res[j] = (*s)[j];
		j++;
	}
	while (s2[j - i])
	{
		res[j] = s2[j - i];
		j++;
	}
	while ((*s)[i])
		res[j++] = (*s)[i++];
	res[j] = 0;
	free(*s);
	*s = res;
	
}

void	update_s_using_flags(int *flags, char **s, char c)
{
	
	if (ft_strchr("id", c) && ft_isdigit(*s[0]))
	{
		if (flags['+'])
			insert_str_at(s, 0, "+");
		else if (flags[' '])
			insert_str_at(s, 0, " ");
	}
	if (flags['#'] && ft_strchr("xX", c))
	{
		if (c == 'x')
			insert_str_at(s, 0, "0x");
		else
			insert_str_at(s, 0, "0X");
	}
	if (c == 'p')
		insert_str_at(s, 0, "0x");
	int len = ft_strlen(*s);
	int j;
	
	if (len < flags['w'])
	{
		j = -1;
		
		if (flags['-'])
		{
			//TODO: this is dump just realloc, memset to spaces and then copy
			while (++j < flags['w'] - len)
				insert_str_at(s, ft_strlen(*s), " ");
		}
		else
		{
			if (flags['0'])
			{
				if (ft_strchr("iduxXp", c))
				{
					int at = !ft_isdigit(*s[0]);
					if (!ft_isdigit(*s[1]))
						at = 2;
					j = -1;
					while (++j < flags['w'] - len)
						insert_str_at(s, at, "0");
				}
				//todo: what about "sc%"?
			}
			else
			{
				j = -1;
				while (++j < flags['w'] - len)
					insert_str_at(s, 0, " ");
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
			i++;
			add_flags(flags, format, &i);
			
			if (!ft_strchr("cspdiuxX%", format[i]))//todo: are u sure we should continue?
				continue;
			char *s = find_initial_s(&ap, format[i]);
			update_s_using_flags(flags, &s, format[i]);
			
			//puts(s);
			bytes_written = write(1, s, ft_strlen(s));//TODO: write fail
			//!!TODO: should we va_arg() here?
			
			if (format[i] != '%') //TODO: does this always work?
				va_arg(ap, int);
			i++;
		
		}
		else
		{
			bytes_written += write(1, &format[i], 1); // TODO: write fail
			i++;
		}
	}
	va_end(ap);
	return (bytes_written);
}	

int main()
{
	#define T(fmt, ...) printf(fmt"\n", __VA_ARGS__), fflush(stdout), ft_printf(fmt"\n", __VA_ARGS__)
	
	T("%-10xt", 42);
}