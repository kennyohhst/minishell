/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/08/04 20:04:18 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_position(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

static bool	expand_edgecases(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

int	special_strlen(char *str)
{
	int	i;

	i = 1;
	while (str[0] && (str[0] == ' ' || str[0] != '$'))
		str++;
	while (str[i] != '\0' && expand_edgecases(str[i]))
		i++;
	return (i);
}

bool	expander(t_data *data, t_input *token)
{
	int start;
	int	len;
	char *temp;
	
	len = 0;
	start = 0;
	while (token)
	{
		if (token && token->token_type == E_VARIABLE)
		{
			start += start_position(token->str);
			len += special_strlen(token->str+start);
			temp = ft_getenv(data->envp, ft_substr(token->str, start+1, len-1));		//LEXER MAKES $USER$PATH 1 token instead of 2 tokens!
			if (!temp)
			{
				token->token_type = STRING;
				return (false);
			}
			free(token->str);
			token->str = ft_strjoin("", temp);
			token->token_type = DQ_STRING;
		}
		len = 0;
		token = token->next;
	}
	return (true);
}



// int	env_end_count(char	*str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			while (str[i] != '\0' && str[i] != ' ')
// 			{
// 				i++;
// 				if (expand_edgecases(str[i]))
// 					return (i);
// 			}
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	count_env(char *str)
// {
// 	int i;
// 	int	x;

// 	x = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			x++;
// 		i++;
// 	}
// 	return (x);
// }
// char	*replace_env(char *str, t_data *data)
// {
// 	char	*temp;
// 	int		i;
// 	int		end_env;

// 	end_env = env_end_count(str);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			temp = ft_substr(str, 0, i);
// 			temp = ft_strjoin(temp, ft_getenv(data->envp, ft_substr(str, i+1,(end_env-i-1))));	
// 			if ((int) ft_strlen(str) != end_env)
// 			{
// 				temp = ft_strjoin(temp, str+end_env);
// 				free(str);
// 				return (temp);
// 			}
// 		}
// 		i++;
// 	}
// 	return (free(str), temp);
// }

// t_input	*expander(t_data *data, t_input *token)
// {
// 	// char *temp;
// 	int	i;

// 	while (token)
// 	{
// 		if (token->token_type == E_VARIABLE)
// 		{
// 			token->token_type = DQE_STRING;
// 		}
// 		if (token->token_type == DQE_STRING)
// 		{
// 			i = count_env(token->str);
// 			while (i--)
// 				token->str = replace_env(token->str, data);
// 			token->token_type = DQ_STRING;
// 		}
// 		token = token->next;
// 	}
// 	return (NULL);
// }



// per word, take and add to new string
// 
