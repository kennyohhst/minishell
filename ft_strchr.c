/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:06:28 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/14 18:33:50 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	slen;

	i = 0;
	slen = ft_strlen(s);
	while (i <= slen)
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i++;
	}
	return (0);
}
