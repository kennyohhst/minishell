/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/25 00:14:27 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

#define USE_STANDARD_FD -1

static void	child_process(t_command *cmd, t_data *data, int fd_in, int fd_out)
{
	if (handle_redirects(cmd, &fd_in, &fd_out) == -1)
		exit (1);
	if (cmd->argv == NULL)
		exit (0);
	if (is_builtin(cmd->argv) == true)
		exit(handle_builtin(cmd, data, fd_in, fd_out));
	if (set_command_path(cmd, data->envp) != 0)
	{
		dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	if (fd_in != USE_STANDARD_FD && dup2(fd_in, STDIN_FILENO) == -1)
		perror("minishell: dup2"); // exit and close?
	if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) == -1)
		perror("minishell: dup2"); // exit and close?
	if (fd_in != USE_STANDARD_FD)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
	execve(cmd->argv[0], cmd->argv, envp_list_to_arr(data->envp));
	perror(cmd->argv[0]);
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

static int	run_command(t_command *cmd, t_data *data, int fd_in, int pipe_fd[2])
{
	pid_t	pid;
	int		fd_out;

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
	if (fd_in != USE_STANDARD_FD)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
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

	// printf("cmd->argv = %p\n", data->command->argv);
	// printf("cmd->argv[0] = %s\n", data->command->argv[0]);
	fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
	{
		perror("minishell: dup");
		return (-1);
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
