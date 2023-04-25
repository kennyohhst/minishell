/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 18:56:41 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/14 22:36:54 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const size_t	needle_len = ft_strlen(needle);
	size_t			i;

	i = 0;
	if (*needle == 0)
		return ((char *) haystack);
	while ((i < len) && haystack[i])
	{
		if ((needle_len + i <= len) && (haystack[i] == *needle))
			if ((ft_strncmp(haystack + i, needle, needle_len)) == 0)
				return ((char *) haystack + i);
		i++;
	}
	return (NULL);
}

/*
    The strnstr() function locates the first occur-
     rence of the null-terminated string needle in the
     string haystack, where not more than len charac-
     ters are searched.  Characters that appear after
     a `\0' character are not searched.  

     If needle is an empty string, haystack is
     returned; if needle occurs nowhere in haystack,
     NULL is returned; otherwise a pointer to the
     first character of the first occurrence of needle
     is returned.
*/