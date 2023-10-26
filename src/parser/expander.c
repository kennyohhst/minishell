/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/10/06 19:06:32 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_edgecase(char c)
{
	if ((ft_isalnum(c) || c == '_')
		&& (c != '\0' && c != ' '))
		return (true);
	return (false);
}

char	*replace_env_with_value(char *input, char *env_var, int start, int end)
{
	char	*first_part;
	char	*second_part;

	if (!env_var)
	{
		first_part = ft_substr(input, 0, start);
		second_part = ft_substr(input + start, end, ft_strlen(input + start) - end);
	}
	else
	{
		first_part = ft_substr(input, 0, start);
		first_part = ft_strjoin_replace(first_part, env_var);
		second_part = ft_substr(input, start + end, ft_strlen(input + start) - end);
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

char	*expander(t_data *data, char *input)
{
	int		end;
	char	*id;
	char	*env_var;
	int		i;

	env_var = NULL;
	i = 0;
	while (i < (int) ft_strlen(input))
	{
		i = skip_singles(i, input);
		i = skip_heredoc(i, input);

		if (input[i] == '$')
		{
			if (is_edgecase(input[i + 1]) == true)
			{
				end = end_position(input + i);
				id = ft_substr(input, i + 1, end - 1);

				env_var = ft_getenv(data->envp, id);
				free(id);

				input = replace_env_with_value(input, env_var, i, end);
			}
		}
		i++;
	}

	// for $? expansion
	while (ft_strnstr(input, "$?", ft_strlen(input)) && single_q(input))
	{
		i = find_start_exit_var(input);
		env_var = ft_itoa(data->exit_code);
		input = replace_env_with_value(input, env_var, i, 2);
		free(env_var);
	}

	return (input);
}
