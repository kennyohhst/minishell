/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_count.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:16:43 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/20 18:18:44 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_count(char *str, char quote_type)
{
	int		i;
	int		count;

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
		return (0);
	}
	return (1);
}

int	check_quotes(char *str)
{
	int		i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (!quote_count(str, str[i]))
				return (0);
		}
		i++;
	}
	return (1);
}
