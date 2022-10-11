#include "ft_printf.h"

//!TODO: make sure we can pass ap as value
void read_value(va_list ap, char c, ft_printf_info_t *info)
{
	info->sp = c;
	if (ft_strchr("id", c))
	{
		info->type = TYPE_INT;
		info->i_value = va_arg(ap, int);
	}
	else if (ft_strchr("xXu", c))
	{
		info->type = TYPE_UINT;
		info->u_value = va_arg(ap, unsigned int);
	}
	else if (c == 'p')
	{
		info->type = TYPE_PTR;
		info->u_value = (size_t)va_arg(ap, void *);
	}
	else if (c == 's')
	{
		info->type = TYPE_STR;
		info->u_value = (size_t)va_arg(ap, char *);
		if (!info->u_value)
			info->u_value = (size_t)"(null)";
	}
	else if (c == 'c')
	{
		info->type = TYPE_CHAR;
		info->i_value = va_arg(ap, int);
	}
	if (ft_strchr("xXp", c))
		info->is_hex = 1;
}

int int_len(int n)
{
	int res;

	res = (n == 0);
	while (n)
	{
		res++;
		n /= 10;
	}
	return (res);
}

int uint_len(size_t n, int hex)
{
	int res;

	res = (n == 0);
	while (n)
	{
		res++;
		if (hex)
			n /= 16;
		else
			n /= 10;
	}
	return (res);
}

//!!TODO: null string
void find_value_width(ft_printf_info_t *info)
{
	if (info->type == TYPE_INT)
		info->width += int_len(info->i_value);
	else if (ft_strchr("xXup", info->sp))
		info->width += uint_len(info->u_value, info->is_hex);
	else if (info->type == TYPE_STR)
	{
		if (info->precision_set && ft_strlen((char *)info->u_value) > (size_t)info->precision_width)
			info->width += info->precision_width;
		else
			info->width += ft_strlen((char *)info->u_value);
	}
	else if (info->type == TYPE_CHAR)
		info->width++;//!TODO: is this right?
	else
		assert(0);
}

void find_width(ft_printf_info_t *info)
{
	//!TODO: precesion behave differently with strings
	find_value_width(info);
	if (info->precision_width > info->width)
	//!TODO: && ft_strchr("iduxX", info->sp) && )
	{
		info->width = info->precision_width;
	}
	if (info->type == TYPE_INT &&
		(info->force_sign || info->force_space || info->i_value < 0))
		info->width++;// ' ' || '+' || '-'
	if (info->is_hex && (info->type == TYPE_PTR || info->hash))
		info->width += 2;// '0x' || '0X'
}

void add_flags(char **fmt, ft_printf_info_t *info)
{
	while (ft_strchr("+- #0", **fmt))
	{
		if (**fmt == '+')
			info->force_sign = 1;
		else if (**fmt == '-')
			info->left_justify = 1;
		else if (**fmt == ' ')
			info->force_space = 1;
		else if (**fmt == '#')
			info->hash = 1;
		else if (**fmt == '0')
			info->padding_with_0 = 1;
		*fmt = *fmt + 1;
	}
	while (ft_isdigit(**fmt))
	{
		info->min_width = info->min_width * 10 + (**fmt - '0');
		*fmt = *fmt + 1;
	}
	if (**fmt == '.')
	{
		info->precision_set = 1;
		*fmt = *fmt + 1;
		while (ft_isdigit(**fmt))
		{
			info->precision_width = info->precision_width * 10 + (**fmt - '0');
			*fmt = *fmt + 1;
		}
	}
}

int ft_printf(const char *fmt, ...)
{
	ft_printf_info_t info = {0};
	va_list	ap;
	va_start(ap, fmt);
	int bytes_written = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_memset(&info, 0, sizeof(info));
			add_flags(&fmt, &info);
			if (!ft_strchr("cspdiuxX%", *fmt))//todo: are u sure we should continue?
				continue;
			if (*fmt == '%')
			{
				bytes_written += write(1, "%", 1);
				fmt++;
				continue;
			}
			read_value(ap, *fmt, &info);
			find_width(&info);
			//
			if (info.precision_set && !info.precision_width && ft_strchr("xXuid", info.sp) && info.i_value == 0 && info.u_value == 0)
				info.width--;
			if (!info.left_justify)
			{
				int w = info.min_width - info.width;
				while (w --> 0)
				{
					if (!info.precision_set && info.padding_with_0)
						bytes_written += write(1, "0", 1);
					else
						bytes_written += write(1, " ", 1);
				}
			}
			//sign or ' '
			if (info.type == TYPE_INT && info.i_value >= 0)
			{
				if (info.force_sign)
					bytes_written += write(1, "+", 1);
				else if (info.force_space)
					bytes_written += write(1, " ", 1);
			}
			//'0x' || '0X'
			if (info.precision_set && !info.precision_width && ft_strchr("xXuid", info.sp) && info.i_value == 0 && info.u_value == 0)
				;
			else
			{

				if (info.type == TYPE_PTR || (info.sp == 'x' && info.hash))
					bytes_written += write(1, "0x", 2);
				if (info.hash && info.sp == 'X')
					bytes_written += write(1, "0X", 2);
				//write the missing zeroes
				if (info.type == TYPE_INT)
				{
					//printf("%d %d\n", info.precision_width, int_len(info.i_value));
					int w = info.precision_width - int_len(info.i_value);
					while (w --> 0)
						bytes_written += write(1, "0", 1);
					bytes_written += ft_putnbr_fd(info.i_value, 1);
				}
				 if (ft_strchr("xXu", info.sp))
				{
					int w = info.precision_width - int_len(info.u_value);
					while (w --> 0)
						bytes_written += write(1, "0", 1);
				}
				if (info.sp == 'u')
					bytes_written += ft_putnbr_base(info.u_value, "0123456789");
				if (ft_strchr("xp", info.sp))
					bytes_written += ft_putnbr_base(info.u_value, "0123456789abcdef");
				if (info.sp == 'X')
					bytes_written += ft_putnbr_base(info.u_value, "0123456789ABCDEF");
				if (info.type == TYPE_STR)
				{
					int l = ft_strlen((char *)info.u_value);
					if (info.precision_set && l > info.precision_width)
						l = info.precision_width;
					for (int i = 0; i < l; i++)
						bytes_written +=write(1,((char *)info.u_value) + i, 1);
				}
				if (info.type == TYPE_CHAR)
					bytes_written += write(1, &info.i_value, 1);
				if (info.left_justify)
				{
					int w = info.min_width - info.width;
					while (w --> 0)
					{
						if (!info.precision_set && info.padding_with_0)
							bytes_written +=  write(1, "0", 1);
						else
							bytes_written += write(1, " ", 1);
					}
				}
			}
			fmt++;
		}
		else
		{
			bytes_written += write(1, fmt, 1); // TODO: write fail
			fmt++;
		}
	}
	va_end(ap);
	return (bytes_written);
}

