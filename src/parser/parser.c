/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:53:38 by opelser           #+#    #+#             */
/*   Updated: 2023/08/20 18:03:32 by kkalika          ###   ########.fr       */
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
			if (token && token->token_type == STRING)
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
		if (token->token_type >= 2 && token->token_type <= 3)
		{
			token = token->next;
			if (token && token->token_type == STRING)
			{
				temp->name = ft_strdup(token->str);
				token = token->next;
			}
		}
	}
	if (token && token->token_type >= 2 && token->token_type <= 3)
		return (o_redirect_type(token, &temp, token->token_type));
	return (token);
}

int	malloc_argv(t_input **token)
{
	int		count;
	t_input	*temp;

	count = 0;
	temp = (*token);
	while (temp)
	{
		if (temp->token_type == PIPE)
			break ;
		if (temp->token_type >= 2 && temp->token_type <= 5)
		{
			temp = temp->next;
			if (temp)
				temp = temp->next;
			continue ;
		}
		else
		{
			count++;
			temp = temp->next;	
		}
	}
	return (count);
}

void	malloc_command_node(t_command **cmd, t_command *temp, t_input **token)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->input = NULL;
	new->output = NULL;
	new->argv = ft_calloc((malloc_argv(token) + 1), sizeof(char *)); // ga hiersow ff malloc juste size doen
	new->arg_count = malloc_argv(token);
	new->argv[new->arg_count] = 0;
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

// t_input	*str_to_argv(t_input *token, t_command **command)
// {
// 	t_command	*temp;

// 	temp = (*command);
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	while (token && token->token_type > 6)
// 	{
// 		temp->argv[(*command)->arg_count] = ft_strdup(token->str);
// 		token = token->next;
// 		(*command)->arg_count++;
// 	}
// 	temp->argv[(*command)->arg_count] = NULL;
// 	return (token);
// }

// t_input	*string_type(t_input *token, t_command **command)
// {
// 	t_command	*temp;

// 	temp = (*command);
// 	while(temp->next != NULL)
// 		temp = temp->next;
// 	while (token)
// 	{
// 			if (token->token_type == STRING) 
// 			{
// 				temp->argv = malloc((list_length(token) + 1) * sizeof(char *));
// 				if (!temp->argv)	
// 					return (NULL);
// 				token = str_to_argv(token, &temp);
// 				continue ;
// 			}
// 			else
// 				return (token);
// 	}
// 	return (token);
// }

t_command	*type_check(t_input *token, t_command **command, t_command *temp)
{
	int i;

	i = -1;
	// malloc_command_node(command, NULL, token);
	while (token)
	{
		if (i < 0)
		{
			malloc_command_node(command, NULL, &token);
			i++;
		}
		if (token->token_type == PIPE)
		{
			i = 0;
			token = token->next;
			malloc_command_node(command, NULL, &token);
		}
		if (!(*command))
			return (NULL);
		temp = (*command);
		while (temp->next != NULL)
			temp = temp->next;
		if (token && token->token_type == STRING)
		{
			temp->argv[i] = ft_strdup(token->str);
			// printf("argv[%d]:	%s\n", i, temp->argv[i]);
			i++;
			token = token->next;
			continue ;
		}
			// token = string_type(token, &temp);
		if (token && (token->token_type == 2 || token->token_type == 3 ))
			token = o_redirect_type(token, &temp->output, token->token_type);
		if (token && (token->token_type == 4 || token->token_type == 5 ))
			token = i_redirect_type(token, &temp->input, token->token_type);
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
// void	malloc_redirects_node(t_redirect **red, int type)
// {
// 	t_redirect	*new;
//  	t_redirect *temp;
	
// 	new = malloc(sizeof(t_redirect));
// 	new->name = NULL;
// 	new->type = (t_token_type) type;
// 	if (!new)
// 		return ;
// 	temp = (*red);
// 	if (temp)
// 	{
// 		while(temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new;
// 		new->next = NULL;
// 	}
// 	else
// 	{
// 		new->next = NULL;
// 		(*red) = new;
// 	}
// }

// t_input	*i_redirect_type(t_input *token, t_redirect **red, int type)
// {
// 	t_redirect	*temp;

// 	if (!token)
// 		return (NULL);
// 	malloc_redirects_node(red, type);
// 	if (!(*red))
// 		return (NULL);
// 	temp = (*red);
// 	while (temp->next)
// 		temp = temp ->next;
// 	if (token)
// 	{
// 		if (token->token_type >= 4 && token->token_type <= 5)
// 		{
// 			token = token->next;
// 			if (token && token->token_type == STRING)
// 			{
// 				temp->name = ft_strdup(token->str);
// 				token = token->next;
// 			}
// 		}
// 	}
// 	if (token && token->token_type >= 4 && token->token_type <= 5)
// 		return (i_redirect_type(token, &temp, token->token_type));
// 	return (token);
// }

// t_input	*o_redirect_type(t_input *token, t_redirect **red, int type)
// {
// 	t_redirect	*temp;

// 	if (!token)
// 		return (NULL);
// 	malloc_redirects_node(red, type);
// 	if (!(*red))
// 		return (NULL);
// 	temp = (*red);
// 	while (temp->next)
// 		temp = temp ->next;
// 	if (token)
// 	{
// 		if (token->token_type >= 2 && token->token_type <= 3)
// 		{
// 			token = token->next;
// 			if (token && token->token_type == STRING)
// 			{
// 				temp->name = ft_strdup(token->str);
// 				token = token->next;
// 			}
// 		}
// 	}
// 	if (token && token->token_type >= 2 && token->token_type <= 3)
// 		return (o_redirect_type(token, &temp, token->token_type));
// 	return (token);
// }

// void	malloc_command_node(t_command **cmd, t_command *temp)
// {
// 	t_command	*new;

// 	new = malloc(sizeof(t_command));
// 	new->input = NULL;
// 	new->output = NULL;
// 	new->argv = NULL;
// 	if (!new)
// 		return ;
// 	temp = (*cmd);
// 	if (temp)
// 	{
// 		while(temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new;
// 		new->next = NULL;
// 	}
// 	else
// 	{
// 		new->next = NULL;
// 		(*cmd) = new;
// 	}
// }

// t_input	*str_to_argv(t_input *token, t_command **command, int i)
// {
// 	t_command	*temp;

// 	temp = (*command);
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	while (token && token->token_type > 6)
// 	{
// 		temp->argv[i] = ft_strdup(token->str);
// 		token = token->next;
// 		i++;
// 	}
// 	temp->argv[i] = NULL;
// 	return (token);
// }

// t_input	*string_type(t_input *token, t_command **command)
// {
// 	t_command	*temp;
// 	int			i;

// 	temp = (*command);
// 	while(temp->next != NULL)
// 		temp = temp->next;
// 	while (token)
// 	{
// 			i = -1;
// 			if (token->token_type >= 6) // this one
// 			{
// 				temp->argv = malloc((list_length(token) + 1) * sizeof(char *));
// 				if (!temp->argv)	
// 					return (NULL);
// 				i++;
// 				token = str_to_argv(token, &temp, i);
// 				continue ;
// 			}
// 			else
// 				return (token);
// 	}
// 	return (token);
// }

// t_command	*type_check(t_input *token, t_command **command, t_command *temp)
// {
// 	malloc_command_node(command, NULL);
// 	while (token)
// 	{
// 		if (token->token_type == PIPE)
// 		{
// 			malloc_command_node(command, NULL);
// 			token = token->next;
// 		}
// 		if (!(*command))
// 			return (NULL);
// 		temp = (*command);
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		if (token && token->token_type >= E_VARIABLE)
// 			token = string_type(token, &temp);
// 		if (token && (token->token_type == 2 || token->token_type == 3 ))
// 			token = o_redirect_type(token, &temp->output, token->token_type);
// 		if (token && (token->token_type == 4 || token->token_type == 5 ))
// 			token = i_redirect_type(token, &temp->input, token->token_type);
// 	}
// 	return (*command);
// }

// t_command	*parser(t_input	*token)
// {
// 	t_command	*command;
	
// 	if (!token)
// 		return (NULL);
// 	command = NULL;
// 	command = type_check(token, &command, NULL);
// 	return (command);
// }
