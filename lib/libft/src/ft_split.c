/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 00:00:19 by opelser       #+#    #+#                 */
/*   Updated: 2022/11/08 22:58:42 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **ptr_arr, int i)
{
	while (ptr_arr[i])
	{
		free(ptr_arr[i]);
		i++;
	}
	free(ptr_arr);
}

static int	ft_mkstr(char const *s, char c, char **ptr_arr, const int count)
{
	int		len;
	int		i;

	i = 0;
	while (count > i)
	{
		len = 0;
		while (*s == c)
			s++;
		while (s[len] && s[len] != c)
			len++;
		ptr_arr[i] = ft_substr(s, 0, len);
		if (ptr_arr[i] == NULL)
		{
			ft_free(ptr_arr, 0);
			return (-1);
		}
		s += len;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr_arr;
	int			i;
	const int	count = ft_count(s, c);

	if (!s)
		return (NULL);
	ptr_arr = malloc((count + 1) * sizeof(char *));
	if (!ptr_arr)
		return (NULL);
	i = ft_mkstr(s, c, ptr_arr, count);
	if (i == -1)
		return (NULL);
	ptr_arr[i] = NULL;
	return (ptr_arr);
}
