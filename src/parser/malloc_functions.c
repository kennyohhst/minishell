/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:33:03 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/14 20:27:25 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	malloc_cmd_node(t_command **cmd, t_command *temp, t_input **token)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return ;
	new->redirects = NULL;
	// new->output = NULL;
	new->argv = ft_calloc((malloc_argv(token) + 1), sizeof(char *));
	if (!new->argv)
		return (free(new));
	new->arg_count = malloc_argv(token);
	new->argv[new->arg_count] = 0;
	temp = (*cmd);
	if (temp)
	{
		while (temp->next != NULL)
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

void	malloc_redirects_node(t_redirect **red, int type)
{
	t_redirect	*new;
	t_redirect	*temp;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->name = NULL;
	new->type = (t_token_type) type;
	temp = (*red);
	if (temp)
	{
		while (temp->next != NULL)
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

int	first_time(t_command **command, t_input **token, int i)
{
	if (i < 0)
	{
		malloc_cmd_node(command, NULL, token);
		i++;
	}
	return (i);
}

int	pipe_encounter(t_command **command, t_input **token, int i)
{
	if ((*token)->token_type == PIPE)
	{
		i = 0;
		(*token) = (*token)->next;
		malloc_cmd_node(command, NULL, token);
	}
	return (i);
}
