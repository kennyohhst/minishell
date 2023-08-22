/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_count.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:16:43 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/22 14:59:50 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_count(char *str, char quote_type, int i)
{
	int		count;

	count = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
			count++;
		if (count == 2)
			return (i);
		i++;
	}
	if ((count % 2) != 0)
	{
		write(2, "unclosed quotes\n", 17);
		return (-1);
	}
	return (i);
}

int	check_quotes(char *str)
{
	int		i;
	char	*temp;
	
	temp = str;
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i = quote_count(temp, str[i], i);
			if (i < 0)
				return (0);
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
