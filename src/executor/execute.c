/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/11/14 12:51:38 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

#define USE_STANDARD_FD -1

static void	child_process(t_command *cmd, t_data *data, int fd_in, int fd_out)
{
	char	**envp;

	if (handle_redirects(cmd, &fd_in, &fd_out) == -1)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv) == true)
		exit(handle_builtin(cmd, data, fd_in, fd_out));
	if (set_command_path(cmd, data->envp) != 0)
	{
		print_error(NULL, cmd->argv[0], "command not found");
		exit(127);
	}
	set_fds(&fd_in, &fd_out);
	close_fds(fd_in, fd_out);
	envp = envp_list_to_arr(data->envp);
	execve(cmd->argv[0], cmd->argv, envp);
	free(envp);
	execve_error(cmd->argv[0]);
}

static int	run_command(t_command *cmd, t_data *data, int fd_in, int pipe_fd[2])
{
	pid_t	pid;
	int		fd_out;

	init_signals(CHILD);
	if (pipe_fd)
		fd_out = pipe_fd[1];
	else
		fd_out = USE_STANDARD_FD;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (pipe_fd)
			close(pipe_fd[0]);
		child_process(cmd, data, fd_in, fd_out);
	}
	close_fds(fd_in, fd_out);
	cmd->pid = pid;
	return (1);
}

int	run_pipeline(t_data *data, int fd_in)
{
	int				pipe_fd[2];
	t_command		*cmd;

	cmd = data->command;
	while (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("minishell : pipe");
			return (-1);
		}
		if (run_command(cmd, data, fd_in, pipe_fd) == -1)
			return (-1);
		fd_in = pipe_fd[0];
		cmd = cmd->next;
	}
	if (run_command(cmd, data, fd_in, NULL) == -1)
		return (-1);
	return (1);
}

int	run_single_command(t_data *data, int fd_in)
{
	int			fd_out;
	t_command	*cmd;
	int			ret;

	cmd = data->command;
	fd_out = USE_STANDARD_FD;
	if (is_builtin(cmd->argv) == true)
	{
		cmd->pid = 0;
		if (handle_redirects(cmd, &fd_in, &fd_out) == -1)
		{
			data->exit_code = 1;
			return (1);
		}
		ret = handle_builtin(cmd, data, fd_in, fd_out);
		if (ret == -1)
			return (1);
		data->exit_code = ret;
	}
	else if (run_command(cmd, data, fd_in, NULL) == -1)
		return (-1);
	return (1);
}

int	execute(t_data *data)
{
	int		fd_in;

	fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
	{
		perror("minishell: dup");
		exit(1);
	}
	if (data->command->next)
	{
		if (run_pipeline(data, fd_in) == -1)
		{
			close(fd_in);
			return (-1);
		}
	}
	else
	{
		if (run_single_command(data, fd_in) == -1)
		{
			close(fd_in);
			return (-1);
		}
	}
	return (1);
}
