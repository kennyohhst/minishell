/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/11/04 23:16:18 by kkalika          ###   ########.fr       */
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

int	d_quotes_token(t_input **cmd, char *str, bool quote)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quote = !quote;
		while (str[i] && !quote && str[i] != '\"')
		{
			i++;
			if (str[i] == '\"')
			{
				quote = !quote;
				break ;
			}
		}
		i++;
		if (quote && (str[i] == '\0' || str[i] == ' ' 
			|| str[i] == '|' || str[i] == '>' || str[i] == '<' || str[i] == '\''))
			return (add_nodes(cmd, NULL
				, ft_substr(str, 0, i), DQ_STRING), i);
	}
	return (-1);
}

int	s_quotes_token(t_input **cmd, char *str, bool quote)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			quote = !quote;
		while (str[i] && !quote && str[i] != '\'')
		{
			i++;
			if (str[i] == '\'')
			{
				quote = !quote;
				break ;
			}
		}
		i++;
		if (quote && (str[i] == '\0' || str[i] == ' ' 
			|| str[i] == '|' || str[i] == '>' || str[i] == '<'))
			return (add_nodes(cmd, NULL
				, ft_substr(str, 0, i), SQ_STRING), i);
	}
	return (-1);
}






			// write(1, "here\n", 5);
			// add_nodes(cmd, NULL, ft_substr(str, 0, i), DQ_STRING);
			// return (1 + i);

			// printf("i = %d		c = %c\n", i, str[i]);
			// printf("node_str:	%s\n", (*cmd)->next->str);



// int	d_quotes_token(t_input **cmd, char *str, bool quote)
// {
// 	int		i;

// 	i = 1;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"')
// 			quote = true;
// 		if (str[i] == '\"' && str[i + 1] == ' ')
// 			return (add_nodes(cmd, NULL
// 					, ft_substr(str, 1, i - 1), DQ_STRING), (i + 1));
// 		i++;
// 	}
// 	if ((str[i] == '\0' && str[i - 1] == '\"') || quote == true)
// 	{
// 		i = remove_quotes(str, '\"');
// 		return (add_nodes(cmd, NULL
// 				, ft_substr(str, 0, i + 1), DQ_STRING), (i + 1));
// 	}
// 	return (-1);
// }

// int	s_quotes_token(t_input **cmd, char *str, bool quote)
// {
// 	int		i;

// 	i = 1;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 			quote = true;
// 		if (str[i] == '\'' && str[i + 1] == ' ')
// 			return (add_nodes(cmd, NULL
// 					, ft_substr(str, 1, i - 1), SQ_STRING), (i + 1));
// 		i++;
// 	}
// 	if ((str[i] == '\0' && str[i - 1] == '\'') || quote == true)
// 	{
// 		i = remove_quotes(str, '\'');
// 		return (add_nodes(cmd, NULL
// 				, ft_substr(str, 0, i + 1), SQ_STRING), (i + 1));
// 	}
// 	return (-1);
// }

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
