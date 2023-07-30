/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 14:39:08 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

#define USE_STANDARD_FD -1

void	close_fds(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

static void	child_process(t_command *cmd, t_envp *envp, int fd_in, int fd_out)
{
	if (set_command_path(cmd, envp) != 0) // "/echo" and "echo/" behave wrong
	{
		dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	if (fd_in >= 0 && dup2(fd_in, STDIN_FILENO) == -1)
		dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_in\n");
	if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) == -1)
		dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_out\n");
	close_fds(fd_in, fd_out);
	execve(cmd->argv[0], cmd->argv, envp_list_to_arr(envp));
	perror(cmd->argv[0]);
	exit(errno);
}

/**
 * @param cmd The current command node
 * @param envp The current envp list
 * @param fd_in File descriptor to read from
 * @param pipe_fd File descriptors of the current pipe
 * @return (pid_t) The pid of the child process created
 */
static int	run_command(t_command *cmd, t_envp *envp, int fd_in, int pipe_fd[2])
{
	pid_t	pid;
	int		fd_out;

	fd_out = USE_STANDARD_FD;
	if (pipe_fd)
		fd_out = pipe_fd[1];
	if (handle_redirects(cmd, &fd_in, &fd_out) == -1)
		return (-1); // doesn't close all fds on fail, should it?
	if (is_builtin(cmd->argv) == true)
		return (handle_builtin(cmd, envp, fd_in, fd_out)); // same here
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (pipe_fd)
			close(pipe_fd[0]);
		child_process(cmd, envp, fd_in, fd_out);
	}
	close_fds(fd_in, fd_out);
	cmd->pid = pid;
	return (1);
}

int	execute(t_command *cmd, t_envp *envp_list)
{
	int		fd_in;
	int		pipe_fd[2];

	fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
		dprintf(STDERR_FILENO, "minishell: failed to dup STDIN\n");
	while (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			dprintf(STDERR_FILENO, "minishell: pipe syscall failed\n");
			return (-1);
		}
		if (run_command(cmd, envp_list, fd_in, pipe_fd) == -1)
			return (-1);
		fd_in = pipe_fd[0];
		cmd = cmd->next;
	}
	if (run_command(cmd, envp_list, fd_in, NULL))
		return (-1);
	return (1);
}
