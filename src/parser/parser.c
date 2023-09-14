/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:53:38 by opelser           #+#    #+#             */
/*   Updated: 2023/09/14 20:26:15 by kkalika          ###   ########.fr       */
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

t_input	*o_redirect_type(t_input *token, t_redirect **red, int type)
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
		return (o_redirect_type(token, &temp, token->token_type));
	return (token);
}

t_command	*type_check(t_input *token, t_command **cmd, t_command *temp, int i)
{
	while (token)
	{
		i = first_time(cmd, &token, i);
		i = pipe_encounter(cmd, &token, i);
		if (!(*cmd))
			return (NULL);
		temp = (*cmd);
		while (temp->next != NULL)
			temp = temp->next;
		if (token && token->token_type >= DQ_STRING)
		{
			temp->argv[i] = ft_strdup(token->str);
			if (!temp->argv[i])
				return (ft_free_str_arr(temp->argv), NULL);
			i++;
			token = token->next;
			continue ;
		}
		if (token && (token->token_type >= 2 || token->token_type <= 5))
			token = o_redirect_type(token, &temp->redirects, token->token_type);
		// if (token && (token->token_type == 4 || token->token_type == 5))
		// 	token = i_redirect_type(token, &temp->input, token->token_type);
	}
	return (*cmd);
}

t_command	*parser(t_input	*token)
{
	t_command	*command;

	if (!token)
		return (NULL);
	command = NULL;
	command = type_check(token, &command, NULL, -1);
	return (command);
}
