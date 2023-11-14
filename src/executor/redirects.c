/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 15:53:15 by opelser       #+#    #+#                 */
/*   Updated: 2023/11/14 12:43:22 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	open_file_with_mode(t_redirect *current)
{
	if (current->type == INPUT_REDIRECT)
		return (open(current->name, O_RDONLY));
	if (current->type == HERE_DOC)
		return (current->heredoc_fd);
	if (current->type == OUTPUT_REDIRECT)
		return (open(current->name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (current->type == APPEND)
		return (open(current->name, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

int	handle_redirects(t_command *cmd, int *fd_in, int *fd_out)
{
	t_redirect		*current;

	current = cmd->redirects;
	while (current)
	{
		if (current->type == INPUT_REDIRECT || current->type == HERE_DOC)
		{
			if (*fd_in >= 0)
				close(*fd_in);
			*fd_in = open_file_with_mode(current);
			if (*fd_in == -1)
				return (perror("minishell"), -1);
		}
		else
		{
			if (*fd_out >= 0)
				close(*fd_out);
			*fd_out = open_file_with_mode(current);
			if (*fd_out == -1)
				return (perror("minishell"), -1);
		}
		current = current->next;
	}
	return (1);
}
