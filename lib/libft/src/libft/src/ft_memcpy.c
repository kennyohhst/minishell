/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 21:00:35 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 18:21:23 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void		*org;
	size_t		i;

	org = dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (n > i)
	{
		((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (org);
}
