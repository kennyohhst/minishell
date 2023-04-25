/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 20:23:13 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 22:35:16 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a substring from the string ’s’.

	The substring begins at index ’start’ and is of maximum size ’len’.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	const size_t	s_len = ft_strlen(s);

	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		len = s_len - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
