/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:43:25 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 18:42:04 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			return ((void *) s);
		n--;
		s++;
	}
	return (NULL);
}
