/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_convert_nums.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 20:12:54 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/10 18:59:00 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversions.h"

int	ft_printf_u(va_list va_ptr)
{
	unsigned int	num;
	int				count;

	num = va_arg(va_ptr, int);
	count = ft_conversion(num, 10, "0123456789");
	return (count);
}

int	ft_printf_hex(va_list va_ptr)
{
	unsigned int	num;
	int				count;

	num = va_arg(va_ptr, int);
	count = ft_conversion(num, 16, "0123456789abcdef");
	return (count);
}

int	ft_printf_hexup(va_list va_ptr)
{
	unsigned int	num;
	int				count;

	num = va_arg(va_ptr, int);
	count = ft_conversion(num, 16, "0123456789ABCDEF");
	return (count);
}

int	ft_printf_di(va_list va_ptr)
{
	long	num;
	int		count;

	num = va_arg(va_ptr, int);
	count = 0;
	if (num < 0)
	{
		count = write(1, "-", 1);
		num *= -1;
	}
	if (count == -1)
		return (-1);
	count += ft_conversion(num, 10, "0123456789");
	return (count);
}

int	ft_printf_p(va_list va_ptr)
{
	unsigned long	ptr;
	int				count;

	ptr = va_arg(va_ptr, unsigned long);
	if (ptr == 0)
		return (write(1, "0x0", 3));
	if (write(1, "0x", 2) == -1)
		return (-1);
	count = ft_conversion(ptr, 16, "0123456789abcdef");
	if (count == -1)
		return (-1);
	return (count + 2);
}
