/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 20:21:03 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 17:48:12 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] < (unsigned char) s2[i])
			return (-1);
		if ((unsigned char) s1[i] > (unsigned char) s2[i])
			return (1);
		i++;
	}
	return (0);
}
