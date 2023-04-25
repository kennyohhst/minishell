/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 22:13:18 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 21:47:31 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;
	const size_t	len = ft_strlen(s);

	i = 0;
	if (!s || !f)
		return (NULL);
	s2 = malloc(len + 1);
	if (!s || !s2)
		return (NULL);
	while (i < (unsigned int)len)
	{
		s2[i] = (*f)(i, s[i]);
		i++;
	}
	s2[i] = 0;
	return (s2);
}
