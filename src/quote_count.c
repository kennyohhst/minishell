/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_count.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:16:43 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/03 18:48:03 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_closed_q(char	*str, char c)
{
	int	i;
	int	q;

	q = 0;
	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == c)
				q++;
			i++;
		}
	}
	if ((q % 2) != 0)
		write(1, "unclosed quotes\n", 17);
	return ((q % 2) == 0);
}

int	quote_count(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == 34)
				return (open_closed_q(str, 34));
			else if (str[i] == 39)
				return (open_closed_q(str, 39));
			i++;
		}				
	}
	return (1);
}
