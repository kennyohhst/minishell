/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:16:43 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/12 16:22:57 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_count(char *str, char quote_type)
{
	int		i;
	int		count;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
			count++;
		i++;
	}
	if ((count % 2) != 0)
	{
		write(1, "unclosed quotes\n", 17);
		exit(0);
	}
	return (1);
}

int	check_quotes(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			int tmp = quote_count(str, str[i]);
			if (str[i] != '\0')
			{
				i++;
				continue;
			}
			// printf("return: %d\n", tmp);			// I'll leave this in so you can debug, but you can remove it after should you feel the need
			return (tmp);
		}
		i++;
	}
	return (1);
}
