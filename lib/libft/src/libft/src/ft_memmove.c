/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:56:29 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 23:07:24 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*uc_dst;
	unsigned char	*uc_src;

	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	if (dst < src)
		while (len--)
			*uc_dst++ = *uc_src++;
	else if (dst > src)
	{
		uc_dst += len - 1;
		uc_src += len - 1;
		while (len--)
			*uc_dst-- = *uc_src--;
	}
	return (dst);
}
