/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 15:53:15 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/02 15:48:52 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/** @return A file descriptor to the created heredoc file or -1 on failure */
int	heredoc(char *delim)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		return (-1);
	write(STDOUT_FILENO, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	while (str && ft_strncmp(delim, str, ft_strlen(str) - 1))
	{
		write(fd[1], str, ft_strlen(str));
		free(str);
		write(STDOUT_FILENO, "> ", 2);
		str = get_next_line(STDIN_FILENO);
	}
	close (fd[1]);
	return (fd[0]);
}

static int	open_file_with_mode(char *name, t_token_type type)
{
	if (type == INPUT_REDIRECT)
		return (open(name, O_RDONLY));
	else if (type == HERE_DOC)
		return (heredoc(name));
	else if (type == OUTPUT_REDIRECT)
		return (open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(name, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

static int	get_last_file(t_redirect **redirect)
{
	t_redirect		*current;
	int				fd;

	fd = 0;
	current = *redirect;
	while (current)
	{
		fd = open_file_with_mode(current->name, current->type);
		if (fd == -1)
		{
			perror(current->name);
			return (-1);
		}
		current->fd = fd;
		if (current->next)
		{
			close(fd);
			*redirect = current->next;
		}
		current = current->next;
	}
	return (1);
}

int	handle_redirects(t_command *cmd, int *fd_in, int *fd_out)
{
	t_redirect	*last_redirect;

	if (cmd->input)
	{
		if (*fd_in >= 0)
			close(*fd_in);
		last_redirect = cmd->input;
		if (get_last_file(&last_redirect) == -1)
			return (-1);
		*fd_in = last_redirect->fd;
	}
	if (cmd->output)
	{
		if (*fd_out >= 0)
			close(*fd_out);
		last_redirect = cmd->output;
		if (get_last_file(&last_redirect) == -1)
			return (-1);
		*fd_out = last_redirect->fd;
	}
	return (1);
}
