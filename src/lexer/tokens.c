/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/11/09 19:48:24 by code             ###   ########.fr       */
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
				return (add_nodes(cmd, NULL, ft_substr(str, 0, 1)
						, INPUT_REDIRECT), 1);
			return (add_nodes(cmd, NULL, ft_substr(str, 0, 1)
					, OUTPUT_REDIRECT), 1);
		}
	}
	return (-1);
}


int	end_of_quotes(char *str, char quote, int i)
{
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	edgecase(char c)
{
	if (c == '\0')
		return (-1);
	else if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (1);
	else if (c == '\"' || c == '\'')
		return (2);	
	return (0);
}

int	after_quotes(char *str, int	i)
{
	while (str[i])
	{
		if (edgecase(str[i]) == 0)
			i++;
		else if (edgecase(str[i]) == -1)
			return (i-1) ;
		else if (edgecase(str[i]) == 1)
			break ;
		else if (edgecase(str[i] == 2))
		{
			i = end_of_quotes(str, str[i], i+1);
			i++;
		}
	}
	return (i-1);
}

int	d_quotes_token(t_input **cmd, char *str)
{
	int		i;
	char 	*temp;

	i = 1;
	i = end_of_quotes(str, '\"', i);
	if (str[i+1])
		i = after_quotes(str, i+1);
	temp = ft_substr(str, 0, i+1);
	add_nodes(cmd, NULL, temp, DQ_STRING);
	return(i+1);
}

int	s_quotes_token(t_input **cmd, char *str)
{
	int		i;
	char 	*temp;

	i = 1;
	i = end_of_quotes(str, '\'', i);
	if (str[i+1])
		i = after_quotes(str, i+1);
	temp = ft_substr(str, 0, i+1);
	add_nodes(cmd, NULL, temp, SQ_STRING);
	return(i+1);
}

int	std_token(t_input **cmd, char *str)
{
	int		i;

	i = 0;
	while (i < (int) ft_strlen(str)+1)
	{
		if (str[i] == ' ' || str[i] == '\0'
			|| str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
		if (str[i] == '\"' || str[i] == '\'')
		{
			i = std_remove_quotes(str, str[i]);
			if (!(*cmd) && i < 0)
				return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
			if (!str[i] || str[i] == ' ')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
			i--;
		}
		i++;
	}
	return (-1);
}
