/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/16 17:41:45 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_position(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && is_edgecase(str[i]))
		i++;
	return (i);
}

int	skip_singles(int i, char *token)
{
	if (token[i] == '\'')
	{
		i++;
		while (token[i] && token[i] != '\'')
			i++;
	}
	return (i);
}

int	find_start_exit_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = skip_singles(i, str);
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				return (i - 1);
		}
		i++;
	}
	return (-1);
}
