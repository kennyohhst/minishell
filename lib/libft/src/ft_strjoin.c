/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 23:33:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/29 19:55:49 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy((char *) str, (char *) s1);
	ft_strcpy((char *) str + s1_len, s2);
	str[s1_len + s2_len] = '\0';
	return (str);
}

char	*ft_strjoin_replace(char *s1, char const *s2)
{
	char	*tmp;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}
