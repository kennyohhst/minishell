/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/05 22:04:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/03/07 20:31:15 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...);
static int		ft_parse(const char *format, va_list va_ptr);
static int		jumptable(const char *format, int specifier, va_list va_ptr);
static int		percent_at_end(int count);

int	ft_printf(const char *format, ...)
{
	va_list		va_ptr;
	int			count;

	va_start(va_ptr, format);
	count = ft_parse(format, va_ptr);
	va_end(va_ptr);
	return (count);
}

static int	ft_parse(const char *format, va_list va_ptr)
{
	int		i;
	int		count;
	int		tmp;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (percent_at_end(count));
			tmp = jumptable(format, (i + 1), va_ptr);
			if (tmp == -1)
				return (-1);
			count += tmp;
			i += 2;
			continue ;
		}
		if (write(1, &format[i], 1) == -1)
			return (-1);
		count++;
		i++;
	}
	return (count);
}

static int	jumptable(const char *format, int specifier, va_list va_ptr)
{
	int						count;
	static const t_function	function_array[256] = {
	['c'] = ft_printf_c,
	['s'] = ft_printf_s,
	['p'] = ft_printf_p,
	['d'] = ft_printf_di,
	['i'] = ft_printf_di,
	['u'] = ft_printf_u,
	['x'] = ft_printf_hex,
	['X'] = ft_printf_hexup,
	['%'] = ft_printf_percent,
	};

	if (function_array[(unsigned char) format[specifier]] == NULL)
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		if (write(1, &format[specifier], 1) == -1)
			return (-1);
		return (2);
	}
	count = function_array[(unsigned char) format[specifier]](va_ptr);
	return (count);
}

static int	percent_at_end(int count)
{
	if ((write(1, "%", 1)) == -1)
		return (-1);
	return (count + 1);
}
