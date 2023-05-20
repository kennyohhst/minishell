/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:27:18 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/20 17:21:51 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *str, char *add_str)
{
	int i = 1;
	
	char	*temp = ft_strnstr(str, add_str, ft_strlen(str));
	if (!ft_isdigit(temp[i]))
	{
		while (ft_isalnum(temp[i]) || temp[i] == '_')
		{
			i++;	
			// printf("test\n");	
		}
	}
	temp = ft_substr(temp, 0, i);
	printf("strnstr_return:	%s\n", temp);
	

	return (NULL);
	//find $
	//save envstring in temp
	//getenv and save string into temp
	//
// 	char	*temp;

// 	temp = str;
// 	while (temp)
// 	{
		
// 	}
}

t_input *expander(t_input *token)
{
	char *temp;

	while (token)
	{
		if (token->token_type == E_VARIABLE)
		{
			temp = getenv((ft_strchr(token->str, '$') + 1));
			free(token->str);
			if (temp)
				token->str = ft_strdup(temp);
			printf("%s\n", token->str);
		}
		if (token->token_type == DQE_STRING)
			replace_env(token->str, "$USER");

		// if (token->token_type == DQE_STRING)
		// {
		// 	char *x_temp = ft_strchr(token->str, '$');
		// 	// printf("%s\n", x_temp);
		// }
		token = token->next;
	}
	return (NULL);
}