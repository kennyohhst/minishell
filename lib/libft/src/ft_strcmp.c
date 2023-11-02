/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:28:03 by opelser           #+#    #+#             */
/*   Updated: 2023/04/28 11:41:23 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char) s1[i] < (unsigned char) s2[i])
			return (-1);
		if ((unsigned char) s1[i] > (unsigned char) s2[i])
			return (1);
		i++;
	}
	return (0);
}
