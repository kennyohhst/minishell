/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/15 16:18:56 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_finder(char *str, char c)
{
	int	i;
	int	count_q;

	count_q = 0;
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == c || (count_q % 2))
		{
			while (str[i] && str[i] != c)
				i++;
			count_q++;
		}
		i++;
	}
	while (str[i] && str[i] != ' ')
		i++;
	if (count_q == 2)
		i++;
	return (i - count_q);
}

int	remove_quotes(char *str, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] != '\0')
			{
				ft_memset(str + i, str[i + 1], 1);
				i++;
				x++;
			}
			i = i - x - 1;
			x = 0;
		}
		i++;
	}
	return (i);
}

int	std_remove_quotes(char *str, char c)
{
	int	i;
	int	x;
	int	len;

	i = 0;
	x = 0;
	len = quotes_finder(str, c);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] != '\0')
			{
				ft_memset(str + i, str[i + 1], 1);
				i++;
				x++;
			}
			i = i - x - 1;
			x = 0;
		}
		i++;
	}
	return (i - len);
}

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

int	d_quotes_token(t_input **cmd, char *str, t_data data)
{
	bool	quote;
	int		i;

	(void) data;
	i = 1;
	quote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quote = true;
		if (str[i] == ' ' && str[i - 1] != '\"')
			i++;
		else if (str[i] == '\"' && str[i + 1] == ' ')
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), DQ_STRING), (i + 1));
		i++;
	}
	if ((str[i] == '\0' && str[i - 1] == '\"') || quote == true)
	{
		i = remove_quotes(str, '\"');
		return (add_nodes(cmd, NULL, ft_substr(str, 0, i+1), DQ_STRING), (i + 1));
	}
	return (-1);
}

int	s_quotes_token(t_input **cmd, char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), SQ_STRING), (i + 1));
		i++;
	}
	return (-1);
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
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i = std_remove_quotes(str, str[i]);
			if (!str[i] || str[i] == ' ')
				return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
			else
				i--;
		}
		i++;
	}
	return (-1);
}
