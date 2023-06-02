/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/06/02 17:11:30 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_d_token(t_input **cmd, char *str, int i, char c)
{
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c)
		{
			if (c == '|')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 2), OR), 2);
			if (c == '>')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 2), APPEND), 2);
			return (add_nodes(cmd, NULL, ft_substr(str, 0, 2), HERE_DOC), 2);
		}
		else
		{
			if (c == '|')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 1), PIPE), 1);
			if (c == '<')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 1), INPUT_REDIRECT), 1);
			return (add_nodes(cmd, NULL, ft_substr(str, 0, 1), OUTPUT_REDIRECT), 1);
		}
	}
	return (-1);
}

int	e_var_token(t_input **cmd, char *str)
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

int	d_quotes_token(t_input **cmd, char *str)
{
	int	i;
	int	e_var;
	
	e_var = 0;
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			e_var++;
		if (str[i] == 34 && i != 1 && e_var == 0)
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), DQ_STRING), (i + 1));
		else if (str[i] == 34 && i != 1 && e_var > 0)
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), DQE_STRING), (i + 1));
		i++;
	}
	return (-1);
}

int	s_quotes_token(t_input **cmd, char *str)
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

int	std_token(t_input **cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == ' ' || str[i] == '\0' 
			|| str[i] == '|' || str[i] == '>' || str[i] == '<'
			|| str[i] == '$' || str[i] == '\"' || str[i] == '\'')
			return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
	}
	return (-1);
}
