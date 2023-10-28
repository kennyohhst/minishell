/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:53:38 by opelser           #+#    #+#             */
/*   Updated: 2023/10/28 19:08:31 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*i_redirect_type(t_input *token, t_redirect **red, int type)
{
	t_redirect	*temp;

	if (!token)
		return (NULL);
	malloc_redirects_node(red, type);
	if (!(*red))
		return (NULL);
	temp = (*red);
	while (temp->next)
		temp = temp ->next;
	if (token)
	{
		if (token->token_type >= 4 && token->token_type <= 5)
		{
			token = token->next;
			if (token && token->token_type >= DQ_STRING)
			{
				temp->name = ft_strdup(token->str);
				token = token->next;
			}
		}
	}
	if (token && token->token_type >= 4 && token->token_type <= 5)
		return (i_redirect_type(token, &temp, token->token_type));
	return (token);
}

t_input	*o_redirect_type(t_input *token, t_redirect **red)
{
	t_redirect	*temp;

	if (!token)
		return (NULL);
	malloc_redirects_node(red, token->token_type);
	if (!(*red))
		return (NULL);
	temp = (*red);
	while (temp->next)
		temp = temp->next;
	if (token)
	{
		if (token->token_type >= 2 && token->token_type <= 5)
		{
			token = token->next;
			if (token && token->token_type >= DQ_STRING)
			{
				temp->name = ft_strdup(token->str);
				token = token->next;
			}
		}
	}
	if (token && token->token_type >= 2 && token->token_type <= 5)
		return (o_redirect_type(token, &temp));
	return (token);
}

static t_input	*process_token(t_command **command, t_input *token, int *i)
{
	t_command	*temp;

	temp = *command;
	while (temp->next != NULL)
		temp = temp->next;
	if (token && token->token_type >= DQ_STRING)
	{
		temp->argv[*i] = ft_strdup(token->str);
		if (!temp->argv[*i])
		{
			ft_free_str_arr(temp->argv);
			return (NULL);
		}
		(*i)++;
		token = token->next;
	}
	else if (token && (token->token_type >= 2 || token->token_type <= 5))
		token = o_redirect_type(token, &temp->redirects);
	return (token);
}

t_command	*type_check(t_input *token)
{
	t_command	*command;
	int			i;

	command = NULL;
	i = 0;
	malloc_cmd_node(&command, NULL, &token);
	while (token)
	{
		i = pipe_encounter(&command, &token, i);
		if (!command)
			return (NULL);
		token = process_token(&command, token, &i);
	}
	return (command);
}

t_command	*parser(t_input	*token)
{
	t_command	*command;

	command = type_check(token);
	return (command);
}
