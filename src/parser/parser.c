/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:53:38 by opelser           #+#    #+#             */
/*   Updated: 2023/06/04 16:24:51 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_redirects_node(t_redirect **red, int type)
{
	t_redirect	*new;
 	t_redirect *temp;
	
	new = malloc(sizeof(t_redirect));
	new->name = NULL;
	new->type = (t_token_type) type;
	if (!new)
		return ;
	temp = (*red);
	if (temp)
	{
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		new->next = NULL;
		(*red) = new;
	}
}

int	encounter_out_red(char *str, t_command **cmd, int type)
{
	t_command	*temp;
	
	temp = (*cmd);
	while (temp->next != NULL)
		temp = temp->next;
	temp->argv = NULL;
	if (str)
		temp->redirects->name = ft_strdup(str);
	else
		temp->redirects->name = NULL;
	temp->redirects->type = type;
	temp->redirects->next = NULL;
	temp->next = NULL;
	return (1);
}

t_input	*redirect_type(t_input *token, t_redirect **red, int type)
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
			if (token && token->token_type == STRING)
			{
				temp->name = ft_strdup(token->str);
				token = token->next;
			}
		}
	}
	if (token && token->token_type >= 2 && token->token_type <= 5)
		return (redirect_type(token, &temp, token->token_type));
	return (token);
}


void	malloc_command_node(t_command **cmd, t_command *temp)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->redirects = NULL;
	new->argv = NULL;
	if (!new)
		return ;
	temp = (*cmd);
	if (temp)
	{
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		new->next = NULL;
		(*cmd) = new;
	}
}

t_input	*str_to_argv(t_input *token, t_command **command, int i)
{
	t_command	*temp;

	temp = (*command);
	while (temp->next != NULL)
		temp = temp->next;
	while (token && token->token_type > 6)
	{
		temp->argv[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	temp->argv[i] = NULL;
	temp->redirects = NULL;
	return (token);
}

void	encounter_pipe(t_command **command)
{
	t_command	*temp;
	
	temp = (*command);
	while (temp->next != NULL)
		temp = temp->next;
	temp->argv = NULL;
	temp->redirects->name = NULL;
	temp->redirects->type = PIPE;
	temp->redirects->next = NULL;
	temp->next = NULL;
}

t_input	*pipe_type(t_input *token, t_command **command)
{
	t_command *temp;

	temp = (*command);
	while (temp->next != NULL)
		temp = temp->next;
	while (token)
	{
		if (token->token_type == PIPE)
		{
			temp->redirects = malloc(sizeof(t_redirect));
			encounter_pipe(&temp);
			token = token->next;
			continue ;
		}
		else
			return (token);
	}
	return (token);
}

t_input	*string_type(t_input *token, t_command **command)
{
	t_command	*temp;
	int			i;

	temp = (*command);
	while(temp->next != NULL)
		temp = temp->next;
	while (token)
	{
			i = -1;
			if (token->token_type > 6)
			{
				temp->argv = malloc((list_length(token) + 1) * sizeof(char *));
				if (!temp->argv)	
					return (NULL);
				i++;
				token = str_to_argv(token, &temp, i);
				continue ;
			}
			else
				return (token);
	}
	return (token);
}



t_command	*type_check(t_input *token, t_command **command, t_command *temp)
{
	while (token)
	{
		malloc_command_node(command, NULL);
		if (!(*command))
			return (NULL);
		temp = (*command);
		while (temp->next != NULL)
			temp = temp->next;
		if (token->token_type > 6)
		{
			token = string_type(token, &temp);
			if (token && token->token_type >= 2 && token->token_type <= 5)
			{
				token = redirect_type(token, &temp->redirects, token->token_type);
				continue;
			}
			continue;
		}			
		if (token && token->token_type == PIPE)
		{
			token = pipe_type(token, &temp);
			continue;
		}
	}
	return (*command);
}


t_command	*parser(t_input	*token)
{
	t_command	*command;
	
	if (!token)
		return (NULL);
	command = NULL;
	command = type_check(token, &command, NULL);
	return (command);
}
