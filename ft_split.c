/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:49:31 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/05 18:09:29 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	wordlen(char *stringy, char delm)
{
	size_t	county;
	size_t	ai;

	ai = 0;
	county = 0;
	while (stringy[ai] == delm && stringy[ai] != '\0')
		ai++;
	while (stringy[ai] != delm && stringy[ai] != '\0')
	{
		county++;
		ai++;
	}
	return (county);
}

static size_t	countwords(char *string, char dlm)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (string[i] != '\0')
	{
		while (string[i] == dlm)
			i++;
		if (string[i] != dlm && string[i] != '\0')
			i++;
		if (string[i] == dlm)
			count++;
		if (string[i] == '\0' && string[(i - 1)] != dlm && dlm != 0)
			count++;
	}
	return (count);
}

static char	**ft_putwords(char *string, char delimiter, char **new_string)
{
	int	i;
	int	wl;
	int	x;

	x = 0;
	wl = 0;
	i = 0;
	while (x < (int) countwords((char *) string, delimiter))
	{
		while (string[i] == delimiter && string[i] != '\0')
			i++;
		if (string[i] != delimiter && string[i] != '\0')
		{
			wl = wordlen((string + i), delimiter);
			new_string[x] = ft_substr(string, i, wl);
		}
		if (!new_string[x])
			return (ft_free_s(new_string), NULL);
		x++;
		i = i + wl;
	}
	new_string[x] = 0;
	return (new_string);
}

char	**ft_split(char const *s, char c)
{
	char	**nstr;

	if (!s)
		return (NULL);
	nstr = malloc(((countwords((char *) s, c) + 1) * sizeof(char *)));
	if (!nstr)
		return (NULL);
	ft_putwords((char *) s, c, nstr);
	return (nstr);
}
