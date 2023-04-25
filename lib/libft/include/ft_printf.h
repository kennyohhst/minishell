/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/05 22:04:57 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/10 19:03:34 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "ft_conversions.h"

typedef int	(*t_function)(va_list);

int		ft_printf(const char *format, ...);

#endif