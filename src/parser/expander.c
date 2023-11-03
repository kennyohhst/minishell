/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/10/28 19:07:29 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env_with_value(char *input, char *env_var, int start, int end)
{
	char	*first_part;
	char	*second_part;

	if (!env_var)
	{
		first_part = ft_substr(input, 0, start);
		second_part = ft_substr(input + start, end,
				ft_strlen(input + start) - end);
	}
	else
	{
		first_part = ft_substr(input, 0, start);
		first_part = ft_strjoin_replace(first_part, env_var);
		second_part = ft_substr(input, start + end,
				ft_strlen(input + start) - end);
	}
	free(input);
	input = ft_strjoin_replace(first_part, second_part);
	free(second_part);
	return (input);
}

int	skip_heredoc(int i, char *str)
{
	int		count;
	int		temp;
	int		length;

	temp = i;
	count = 0;
	length = ft_strlen(str) - 1 - temp;
	while (str && length-- > 0 && str[i])
	{
		while (length-- > 0 && str[i] == '<')
		{
			count++;
			i++;
		}
		if (count == 2)
		{
			if (str[i] && str[i] == '$')
				return (i + 1);
		}
		else
			count = 0;
		length--;
		i++;
	}
	return (temp);
}

bool	single_q(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == '$')
					return (false);
				i++;
			}
		}
		i++;
	}
	return (true);
}

static char	*handle_dollar_var(t_data *data, char *input, int *i)
{
	int		end;
	char	*id;
	char	*env_var;

	if (input[*i] == '$' && is_edgecase(input[*i + 1]) == true)
	{
		end = end_position(input + *i);
		id = ft_substr(input, *i + 1, end - 1);
		env_var = ft_getenv(data->envp, id);
		free(id);
		input = replace_env_with_value(input, env_var, *i, end);
		(*i) += end;
	}
	else
		(*i)++;
	return (input);
}

char	*expander(t_data *data, char *input)
{
	int		i;
	char	*env_var;
	int		q;

	i = 0;
	q = -1;
	while (i < (int) ft_strlen(input))
	{
		if (input[i] == '\"' && input[i++] != '\0')
			q *= -1;
		if (q == -1)
			i = skip_singles(i, input);
		i = skip_heredoc(i, input);
		input = handle_dollar_var(data, input, &i);
	}
	while (ft_strnstr(input, "$?", ft_strlen(input)))
	{
		i = find_start_exit_var(input);
		if (i == -1)
			break ;
		env_var = ft_itoa(data->exit_code);
		input = replace_env_with_value(input, env_var, i, 2);
		free(env_var);
	}
	return (input);
}