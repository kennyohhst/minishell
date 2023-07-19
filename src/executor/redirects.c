/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 15:53:15 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 14:50:51 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static t_redirect	*get_last_node(t_redirect *redirect)
{
	while (redirect->next)
		redirect = redirect->next;
	return (redirect);
}

/**	
 * @brief Sets the fd field in the given redirect node
 * @return -1 on error or 1 on succes
*/
static int	set_redirect_fd(t_redirect *redirect)
{
	int				fd;
	t_token_type	type;

	fd = 0;
	type = redirect->type;
	if (type == INPUT_REDIRECT)
		fd = open(redirect->name, O_RDONLY);
	else if (type == HERE_DOC)
		fd = heredoc(redirect->name);
	else if (type == OUTPUT_REDIRECT)
		fd = open(redirect->name, O_WRONLY);
	else if (type == APPEND)
		fd = open(redirect->name, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror(C_BOLD""C_RED"open error\n"C_RESET);
		return (-1);
	}
	redirect->fd = fd;
	return (1);
}

int	handle_redirects(t_command *cmd, int *fd_in, int *fd_out)
{
	t_redirect	*last_redirect;

	if (cmd->input)
	{
		close(*fd_in);
		last_redirect = get_last_node(cmd->input);
		if (set_redirect_fd(last_redirect) == -1)
			return (-1);
		*fd_in = last_redirect->fd;
	}
	if (cmd->output)
	{
		close(*fd_out);
		last_redirect = get_last_node(cmd->output);
		if (set_redirect_fd(last_redirect) == -1)
			return (-1);
		*fd_out = last_redirect->fd;
	}
	return (1);
}

void	create_output_files(t_command *cmd)
{
	t_redirect	*output;
	int			fd;

	while (cmd)
	{
		output = cmd->output;
		while (output)
		{
			fd = open(output->name, O_CREAT | O_WRONLY, 0644);
			if (fd == -1)
				return ;
			close(fd);
			output = output->next;
		}
		cmd = cmd->next;
	}
}
