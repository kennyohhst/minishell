/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 22:53:38 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/17 23:24:39 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*create_new_node(t_input *tokens)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = get_command_argv(tokens);
	if (!command->argv)
	{
		free(command);
		return (NULL);
	}
	command->redirects = NULL;
	command->next = NULL;
	return (command);
}

t_command	*parser(t_input *tokens)
{
	t_command	*command;

	if (!tokens)
		return (NULL);
	command = create_new_node(tokens);
	if (!command)
		return (NULL);
	return (command);
}
