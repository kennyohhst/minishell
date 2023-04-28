/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/28 16:50:19 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_d_token(t_token **cmd, char *str, int i, char c)
{
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c)
		{
			if (c == '|')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 2), PIPE_2), 2);
			if (c == '>')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 2), O_RED_2), 2);
			return (add_nodes(cmd, NULL, ft_substr(str, 0, 2), I_RED_2), 2);
		}
		else
		{
			if (c == '|')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 1), PIPE_1), 1);
			if (c == '<')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 1), I_RED_1), 1);
			return (add_nodes(cmd, NULL, ft_substr(str, 0, 1), O_RED_1), 1);
		}
	}
	return (-1);
}

int	e_var_token(t_token **cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == 32 || str[i] == '\0')
			return (add_nodes(cmd, NULL, ft_substr(str, 0, i), E_VARIABLE), i);
	}
	return (i);
}

int	d_quotes_token(t_token **cmd, char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && i != 1)
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), DQ_STRING), (i + 1));
		i++;
	}
	return (-1);
}

int	s_quotes_token(t_token **cmd, char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), SQ_STRING), (i + 1));
		i++;
	}
	return (-1);
}

int	std_token(t_token **cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == 32 || str[i] == '\0' || str[i] == 34 || str[i] == 39)
			return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
	}
	return (-1);
}
