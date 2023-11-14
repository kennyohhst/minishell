/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:30:44 by opelser           #+#    #+#             */
/*   Updated: 2023/11/09 21:58:52 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

char	*get_file_name(void)
{
	static int		file_count = 0;
	char			*name;
	char			*number;

	file_count++;
	number = ft_itoa(file_count);
	if (!number)
	{
		print_error("malloc", NULL, "get_file_name");
		exit(EXIT_FAILURE);
	}
	name = ft_strjoin("/tmp/heredoc", number);
	if (!name)
	{
		print_error("malloc", NULL, "get_file_name");
		exit(EXIT_FAILURE);
	}
	free(number);
	return (name);
}

static int	get_input(char *file_name, char *delim)
{
	char	*str;
	int		fd;

	init_signals(HEREDOC);
	fd = open(file_name, O_WRONLY);
	if (fd == -1)
	{
		print_error("open", NULL, "get_input");
		exit(EXIT_FAILURE);
	}
	unlink(file_name);
	str = readline("> ");
	while (str && ft_strcmp(delim, str))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
	exit(EXIT_SUCCESS);
}

static int	wait_heredoc(t_data *data, pid_t pid, int fd)
{
	int			w_status;

	w_status = 0;
	waitpid(pid, &w_status, 0);
	if (WEXITSTATUS(w_status) != EXIT_SUCCESS)
	{
		close(fd);
		data->exit_code = WEXITSTATUS(w_status);
		return (-1);
	}
	if (WIFSIGNALED(w_status))
	{
		close(fd);
		data->exit_code = 128 + WTERMSIG(w_status);
		return (-1);
	}
	return (fd);
}

static int	get_heredoc_fd(t_data *data, char *name)
{
	char		*file_name;
	pid_t		pid;
	int			fd;

	file_name = get_file_name();
	init_signals(IGNORE);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error("open", NULL, "get_heredoc_fd");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		print_error("fork", NULL, "get_heredoc_fd");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		get_input(file_name, name);
	free(file_name);
	return (wait_heredoc(data, pid, fd));
}

static int	find_heredoc(t_data *data, t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == HERE_DOC)
		{
			redirect->heredoc_fd = get_heredoc_fd(data, redirect->name);
			if (redirect->heredoc_fd == -1)
				return (-1);
		}
		redirect = redirect->next;
	}
	return (0);
}

static void	close_heredoc(t_command *command)
{
	t_redirect	*redirect;

	while (command)
	{
		redirect = command->redirects;
		while (redirect)
		{
			if (redirect->heredoc_fd != -1)
				close(redirect->heredoc_fd);
			redirect = redirect->next;
		}
		command = command->next;
	}
}

int	handle_heredoc(t_data *data)
{
	t_command	*temp;

	temp = data->command;
	while (temp)
	{
		if (find_heredoc(data, temp->redirects) == -1)
		{
			close_heredoc(data->command);
			free_cmd(data->command);
			return (-1);
		}
		temp = temp->next;
	}
	return (0);
}
