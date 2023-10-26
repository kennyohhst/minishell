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

bool	expand_edgecases(char c)
{
	if (c != '\0' && (ft_isalnum(c) || c == '_') && c != ' ')
		return (true);
	return (false);
}

char	*replace_env_with_value(char *token, char *e_var, int start, int end)
{
	char	*temp_s;
	char	*temp_e;

	if (start == -1)
		return (token);
	if (!e_var)
	{
		temp_s = ft_substr(token, 0, (start));
		temp_e = ft_substr(token + start, end, (ft_strlen(token) - end));
		free(token);
		token = ft_strjoin_replace(temp_s, temp_e);
		return (token);
	}
	else
	{
		temp_s = ft_substr(token, 0, (start));
		temp_e = ft_substr(token, end + start, ft_strlen(token + end + start));
		temp_s = ft_strjoin_replace(temp_s, e_var);
		free(token);
		token = ft_strjoin_replace(temp_s, temp_e);
		return (token);
	}
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

bool	expander(t_data *data, char **tkn, char *temp, int i)
{
	int		end;

	while (i < (int) ft_strlen((*tkn)))
	{
		i = skip_singles(i, (*tkn));
		i = skip_heredoc(i, (*tkn));
		if ((*tkn)[i] == '$')
		{
			if (expand_edgecases((*tkn)[i + 1]))
			{
				end = end_position((*tkn) + i);
				temp = ft_getenv(data->envp,
						ft_substr((*tkn), i + 1, end - 1));
				(*tkn) = replace_env_with_value((*tkn), temp, i, end);
			}
		}
		i++;
	}
	while (ft_strnstr((*tkn), "$?", ft_strlen((*tkn))) && single_q((*tkn)))
	{
		i = find_start_exit_var(*tkn);
		temp = ft_itoa(data->exit_code);
		(*tkn) = replace_env_with_value((*tkn), temp, i, 2);
	}
	return (false);
}
