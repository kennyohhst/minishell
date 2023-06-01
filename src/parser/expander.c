/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/26 16:23:02 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, t_envp *envp)
{
	char	*temp;
	
	if (!str)
		return (NULL);
	while (envp)
	{
		if (!ft_strcmp(str, envp->id))
		{
			temp = ft_strdup(envp->value);
			return (temp);
		}
		envp = envp->next;
	}
	return (NULL);
}

int	count_env(char *str)
{
	int i;
	int	x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			x++;
		i++;
	}
	return (x);
}

int	env_end_count(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] != '\0' && str[i] != ' ')
			{
				i++;
				if (str[i] == ' ' || str[i] == ',' || str[i] == 39 || str[i] == '\0')
					return (i);
			}
		}
		i++;
	}
	return (0);
}

char	*replace_env(char *str, t_data *data)
{
	char	*temp;
	int		i;
	int		end_env;

	end_env = env_end_count(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			temp = ft_substr(str, 0, i);
			temp = ft_strjoin(temp, ft_getenv(ft_substr(str, i+1,(end_env-i-1)), data->envp));
			if ((int) ft_strlen(str) != end_env)
			{
				temp = ft_strjoin(temp, str+end_env);
				free(str);
				return (temp);
			}
		}
		i++;
	}
	return (free(str), temp);
}

t_input *expander(t_input *token, t_data *data)
{
	char *temp;
	int	i;

	while (token)
	{
		if (token->token_type == E_VARIABLE)
		{
			temp = ft_getenv((ft_strchr(token->str, '$') + 1), data->envp);
			if (temp)
			{
				free(token->str);
				token->str = ft_strdup(temp);
				token->token_type = STRING;
			}
		}
		if (token->token_type == DQE_STRING)
		{
			i = count_env(token->str);
			while (i--)
				token->str = replace_env(token->str, data);
			token->token_type = DQ_STRING;
		}
		token = token->next;
	}
	return (NULL);
}
