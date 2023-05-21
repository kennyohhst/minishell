/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:16:43 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/21 20:04:50 by kkalika          ###   ########.fr       */
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
		{
			i += 2;
			continue ;
		}
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
