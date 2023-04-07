/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:04:49 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/05 18:16:30 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*sauce;
	size_t	i;

	if (!src || !dst || n <= 0)
		return (0);
	dest = (char *) dst;
	sauce = (char *) src;
	i = 0;
	while (n != i)
	{
		dest[i] = sauce[i];
		i++;
	}
	return (dst);
}
