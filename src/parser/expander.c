/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/08/15 20:50:47 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_single_quotes(char *str, int i)
{
	if (str[i] && str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i);
}
static int	start_position(char *str)
{
	int	i;

	i = skip_single_quotes(str, 0);
	while (str[i] && str[i] != '$')
	{
		i = skip_single_quotes(str, i);
		i++;
	}
	return (i);
}

static bool	expand_edgecases(char c)
{
	if (ft_isalnum(c) || c == '_')
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
char	*replace_env_with_value(char *token, char *env_value, int start, int end)
{
	char	*temp_s;
	char	*temp_e;
	
	if (!env_value)
	{
		temp_s = ft_substr(token, 0, (start));
		temp_e = ft_substr(token+start, end, (ft_strlen(token) - end));
		free(token);
		token = ft_strjoin_replace(temp_s, temp_e);
		return (token);
	}
	else
	{
		temp_s = ft_substr(token, 0, (start));
		temp_e = ft_substr(token, end+start, ft_strlen(token+end+start));
		temp_s = ft_strjoin_replace(temp_s, env_value);
		free(token);
		token = ft_strjoin_replace(temp_s, temp_e);
		return (token);
	}
}
char	*exit_code_expand(char *token, t_data data, int start, int end)
{
	char	*temp_s;
	char	*temp_e;

	if (token[end] == '?')
	{
		temp_s = ft_substr(token, 0, start);
		temp_e = ft_substr(token, end+1, ft_strlen(token+end+start));
		temp_s = ft_strjoin_replace(temp_s, ft_itoa(data.exit_code));
		// free(token);
		token = ft_strjoin_replace(temp_s, temp_e);
		return (token);
	}
	else
		return (token);
}
char	*strchr_skip_single_quotes(const char *s, int c)
{
	int		i;

	i = skip_single_quotes((char *) s, 0);
	while (s[i])
	{
		i = skip_single_quotes((char *) s, i);
		if (s[i] == (char) c)
			return ((char *) s + i);
		else if (!s[i])
			return (NULL);
		i++;
	}
	return (NULL);
}

bool	expander(t_data data, char **token)
{
	int start;
	int	end;
	char *temp;
	
	end = 0;
	start = 0;
	while (strchr_skip_single_quotes((*token), '$') != NULL)
	{
		start = start_position((*token));
		end = end_position((*token)+start);
		if (ft_strnstr((*token), "$?", ft_strlen((*token))))
		{
			temp = ft_itoa(data.exit_code);
			end++;
		}
		else
			temp = ft_getenv(data.envp, ft_substr((*token), start+1, end-1));
		(*token) = replace_env_with_value((*token), temp, start, end);
		start = 0;
		end = 0;
	}
	return (true);
}
