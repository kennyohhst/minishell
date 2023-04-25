/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conversions.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 18:54:13 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/10 19:08:08 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERSIONS_H
# define FT_CONVERSIONS_H

# include <stdarg.h>
# include <unistd.h>

int		ft_conversion(unsigned long num, int base, char *characters);

int		ft_printf_c(va_list va_ptr);
int		ft_printf_s(va_list va_ptr);
int		ft_printf_p(va_list va_ptr);
int		ft_printf_di(va_list va_ptr);

int		ft_printf_u(va_list va_ptr);
int		ft_printf_hex(va_list va_ptr);
int		ft_printf_hexup(va_list va_ptr);
int		ft_printf_percent(va_list va_ptr);

#endif