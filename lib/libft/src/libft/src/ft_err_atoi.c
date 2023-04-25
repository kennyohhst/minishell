/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_err_atoi.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 17:06:26 by opelser       #+#    #+#                 */
/*   Updated: 2023/04/25 22:31:14 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	The atoi() function converts the initial portion of the string
		pointed to by nptr to int. The converted value or 0 on error.
*/

#include <limits.h>
#include "libft.h"

static int	get_first_num(const char *str, int *sign)
{
	int		i;

	i = 0;
	*sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_err_atoi(const char *str, int *result)
{
	int		sign;
	int		i;
	long	tmp;

	tmp = 0;
	i = get_first_num(str, &sign);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		tmp = tmp * 10 + (str[i] - '0');
		i++;
	}
	tmp *= sign;
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (0);
	*result = tmp;
	return (1);
}

// #include "libft.h"
// int	main()
// {
// 	const char	str[] = "2147483649";

// 	printf("%d\n", ft_atoi(str));

// 	printf("%d", atoi(str));
// }