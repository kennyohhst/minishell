/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/08/15 20:15:50 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes(char *str, char c)
{
	int	len;
	int i;
	int	x;
	
	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			len = i;
			while (str[i] != '\0')
			{
				ft_memset(str+i, str[i+1], 1);
				i++;
				x++;
			}
			i = i - x;
			x = 0;
		}
		i++;
	}
	return (len);
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
	(void) cmd;
	while (str[i] != '\0')
	{
		i++;
		// if (str[i] == ' ' || str[i] == '\0' || str[i] == '$' || str[i] == '\"')
			//expand here already?
	}
	return (i);


	
	// int	i;

	// i = 0;
	// while (str[i] != '\0')
	// {
	// 	i++;
	// 	if (str[i] == ' ' || str[i] == '\0' || str[i] == '$' || str[i] == '\"')
	// 		return (add_nodes(cmd, NULL, ft_substr(str, 0, i), E_VARIABLE), i);
	// }
	// return (i);
}

void	move_quote(char *str)
{
	int	i;
	char	*quote;
	char	*s;

	i = 0;
	quote = ft_memchr(str+1, '\"', ft_strlen(str)-1);
	s = quote;
	s++;
	while (s[i] != '\0' && s[i] != '<' && s[i] != '>' && s[i] != '|' && s[i] != ' ')
		i++;
	ft_memmove(quote, s, i);
	ft_memset(quote+i, '\"', 1);
}

int	d_quotes_token(t_input **cmd, char *str, t_data data)
{
	int	i;
	int	e_var;
	(void) data;
	
	e_var = 0;
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			e_var++;
		if (str[i] == '\"' && i != 1 && e_var == 0)
			return (add_nodes(cmd, NULL, ft_substr(str, 1, i - 1), DQ_STRING), (i + 1));
		else if (str[i] == '\"' && i != 1 && e_var > 0)
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
		if (str[i] == '\'')
			return (add_nodes(cmd, NULL
					, ft_substr(str, 1, i - 1), SQ_STRING), (i + 1));
		i++;
	}
	return (-1);
}
int	check_env(char *str)
{
	int i;

	i = 1;
	while (str && str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	std_token(t_input **cmd, char *str)
{
	int		i;

	i = 0;
	while (i < (int) ft_strlen(str)+1)
	{
		if (str[i] == ' ' || str[i] == '\0' || str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i = remove_quotes(str, str[i]);
			if (!str[i])
				return (add_nodes(cmd, NULL, ft_substr(str, 0, i), STRING), i);
			else
				i--;
		}
		i++;
	}
	return (-1);
}
