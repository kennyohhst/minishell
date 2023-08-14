/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:27:18 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/11 01:18:15 by kkalika       ########   odam.nl         */
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
		temp_e = ft_substr(token, end, (ft_strlen(token) - end));
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
	
	// printf("start + end = total\n");
	// printf("%d	  +	%d	= %d\n", start, end, start+end);

	if (token[end] == '?')
	{
		temp_s = ft_substr(token, 0, start);
		temp_e = ft_substr(token, end+start+1, ft_strlen(token+end+start));
		temp_s = ft_strjoin_replace(temp_s, ft_itoa(data.exit_code));
		free(token);
		token = ft_strjoin_replace(temp_s, temp_e);
		return (token);
	}
	else
		return (token);
}
bool	expander(t_data data, t_input *token)
{
	int start;
	int	end;
	char *temp;
	
	end = 0;
	start = 0;
	while (token)
	{
		while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
		{
			start = start_position(token->str);
			end = end_position(token->str+start);
			printf("end = %d\n", end);
			temp = ft_getenv(data.envp, ft_substr(token->str, start+1, end-1));		//LEXER MAKES $USER$PATH 1 token instead of 2 tokens!
			// if (token->str[end] == '?')
			// 	token->str = exit_code_expand(token->str, data, start, end);
			// else
				token->str = replace_env_with_value(token->str, temp, start, end);
		}
		end = 0;
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
		// temp_e = ft_substr(token, end, (ft_strlen(token) - end));
