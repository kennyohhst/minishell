/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_convert.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 19:09:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/10 18:58:56 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversions.h"

typedef int	(*t_function)(va_list);

int	ft_printf_c(va_list va_ptr)
{
	char	arg;

	arg = (char)va_arg(va_ptr, int);
	return (write(1, &arg, 1));
}

int	ft_printf_s(va_list va_ptr)
{
	char	*str;
	int		count;
	int		tmp;
	int		i;

	str = va_arg(va_ptr, char *);
	if (str == NULL)
		return (write(1, "(null)", 6));
	i = 0;
	count = 0;
	while (str[i])
	{
		tmp = write(1, &str[i], 1);
		if (tmp == -1)
			return (-1);
		count += tmp;
		i++;
	}
	return (count);
}

int	ft_printf_percent(va_list va_ptr)
{
	(void) va_ptr;
	return (write(1, "%", 1));
}
