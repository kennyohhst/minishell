/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:16:43 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/20 21:39:54 by code             ###   ########.fr       */
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
		if (str[i] == '\\')
			i += 2;
		if (str[i] == quote_type)
			count++;
		i++;
	}
	if ((count % 2) != 0)
	{
		write(1, "unclosed quotes\n", 17);
		// exit(0);
	}
	return (i);
}

int	check_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i = quote_count(str, str[i]);
			if (str[i] != '\0')
			{
				i++;
				continue;
			}
			return (1);
		}
		i++;
	}
	return (1);
}
