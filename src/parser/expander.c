/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/15 17:28:40 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand_edgecases(char c)
{
	if (c != '\0' && (ft_isalnum(c) || c == '_') && c != ' ')
		return (true);
	return (false);
}

int	end_position(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && expand_edgecases(str[i]))
		i++;
	return (i);
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

int	skip_singles(int i, char *token)
{
	if (token[i] == '\'')
	{
		i++;
		while (token[i] && token[i] != '\'')
			i++;
	}
	return (i);
}

int	find_start_exit_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = skip_singles(i, str);
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				return (i-1);
		}
		i++;
	}
	return (-1);
}

bool	expander(t_data data, char **token, char *temp, int i)
{
	int		end;

	while (i < (int) ft_strlen((*token)))
	{
		i = skip_singles(i, (*token));
		if ((*token)[i] == '$')
		{
			if (expand_edgecases((*token)[i + 1]))
			{
				end = end_position((*token) + i);
				temp = ft_getenv(data.envp, 
				ft_substr((*token), i + 1, end - 1));
				(*token) = replace_env_with_value((*token), temp, i, end);
			}
		}
		i++;
	}
	if (ft_strnstr((*token), "$?", ft_strlen((*token))))
	{
		i = find_start_exit_var(*token);
		temp = ft_itoa(data.exit_code);
		(*token) = replace_env_with_value((*token), temp, i, 2);
	}
	return (false);
}
