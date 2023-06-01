/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:53:38 by opelser           #+#    #+#             */
/*   Updated: 2023/06/01 19:40:06 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_node(t_command **cmd, t_command *temp)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
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
	temp->redirects->type = PIPE_1;
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
		if (token->token_type == PIPE_1)
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



t_command	*type_check(t_input *token, t_command **command)
{
	t_command	*temp;
	while (token)
	{
		malloc_node(command, NULL);
		if (!(*command))
			return (NULL);
		temp = (*command);
		while (temp->next != NULL)
			temp = temp->next;
		
		if (token->token_type == STRING)
		{
			token = string_type(token, &temp);
			continue ;
		}
		token = pipe_type(token, &temp);
		// output_redirect_type();	// >
		// append_operator_type();	// >>
		// input_redirection_type(); // <
		// here_doc_type(); // <<
	}
	return (*command);
}


t_command	*parser(t_input	*token)
{
	t_command	*command;
	
	if (!token)
		return (NULL);
	command = NULL;	
	command = type_check(token, &command);
	return (command);
}



























// static t_command	*create_new_node(t_input *tokens)
// {
// 	t_command	*command;

// 	command = malloc(sizeof(t_command));
// 	if (!command)
// 		return (NULL);
	
// 	//it takes all the >6 types and pushes into argv
// 	//if < 6, returns the argv, but do we want that?

// 	get_command_argv(tokens, &command);
// 	printf("command->redirects:	%u\n", command->redirects->type);
// 	if (!command->argv)
// 	{
// 		free(command);
// 		return (NULL);
// 	}
// 	command->redirects = NULL;
// 	command->next = NULL;
// 	return (command);
// }

// t_command	*parser(t_input *tokens)
// {
// 	t_command	*command;

// 	if (!tokens)
// 		return (NULL);
// 	command = create_new_node(tokens);
// 	if (!command)
// 		return (NULL);
// 	return (command);
// }
