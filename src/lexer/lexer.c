/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:49 by kkalika           #+#    #+#             */
/*   Updated: 2023/10/28 18:27:44 by code             ###   ########.fr       */
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

t_input	*lexer(char *input, t_data *data)
{
	t_input		*input_list;

	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	ft_bzero(&input_list, sizeof(t_input *));
	if (!check_quotes(input))
	{
		data->exit_code = 2;
		return (NULL);
	}
	create_input_list(&input_list, input, data);
	if (!valid_input_check(input_list))
	{
		data->exit_code = 2;
		free_tokens(input_list);
		return (NULL);
	}
	return (input_list);
}
