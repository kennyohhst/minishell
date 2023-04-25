/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:16:43 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/21 13:34:09 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_closed_q(char	*str, char c)
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
	return ((q % 2) == 0);
}

int	quote_count(char *str)
{
	int		i;
	int		count_d;
	int		count_s;

	count_d = 0;
	count_s = 0;
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
