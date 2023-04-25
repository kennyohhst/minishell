/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 13:54:06 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 18:40:20 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*temp;

	temp = b;
	i = 0;
	while (len > i)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
