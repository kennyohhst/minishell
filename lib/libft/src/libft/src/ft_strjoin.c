/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 23:33:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/05 18:32:26 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		str[i + s1_len] = s2[i];
		i++;
	}
	str[s1_len + s2_len] = '\0';
	return (str);
}
