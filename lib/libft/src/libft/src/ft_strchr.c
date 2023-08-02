/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 19:33:52 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/02 16:11:57 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i - 1])
	{
		if (s[i] == (char) c)
			return ((char *) s + i);
		i++;
	}
	return (NULL);
}

int	ft_strchr_index(char *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}
