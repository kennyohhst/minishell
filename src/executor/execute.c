/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/28 16:21:15 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/errno.h>
#define READ 0
#define WRITE 1

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

/**
 * @param cmd The current command node
 * @param envp The current envp list
 * @param fd_in File descriptor to read from
 * @param fd_out File descriptor to write to
 * @param pipe_read File descriptor of the pipe to close in the child so it
 * 					doesn't hang
 * @return (pid_t) The pid of the child process created
 */
static pid_t run_command(t_command *cmd, t_envp *envp, 
	int fd_in, int fd_out, int pipe_read)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (set_command_path(cmd, envp) != 0)
		{
			dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv[0]);
			exit(127);
		}
		if (pipe_read >= 0)
			close(pipe_read);
		if (fd_in >= 0 && dup2(fd_in, STDIN_FILENO) == -1)
			dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_in\n");
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) == -1)
			dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_out\n");
		close_pipe(fd_in, fd_out);
		execve(cmd->argv[0], cmd->argv, envp_list_to_arr(envp));
		perror(cmd->argv[0]);
		exit(errno);
	}
	close_pipe(fd_in, fd_out);
	return (pid);
}

int	execute(t_command *cmd, t_envp *envp_list)
{
	int		fd_in;
	int		new_pipe[2];

	create_output_files(cmd);
	fd_in = dup(STDIN_FILENO); // open new fd pointing to STDIN
	if (fd_in == -1)
		dprintf(STDERR_FILENO, "minishell: failed to dup STDIN\n");
	while (cmd->next)
	{
		if (pipe(new_pipe) == -1)
		{
			dprintf(STDERR_FILENO, "minishell: pipe syscall failed\n");
			return (-1);
		}
		if (handle_redirects(cmd, &fd_in, &new_pipe[1]) == -1)
			return (-1);
		cmd->pid = run_command(cmd, envp_list, fd_in, new_pipe[1], new_pipe[0]); // run command with fd_in being STDIN or the previous pipes read end and new pipes write end
		fd_in = new_pipe[0];
		cmd = cmd->next;
	}
	cmd->pid = run_command(cmd, envp_list, fd_in, -1, -1); // run command with the output going to STDOUT
	return (1);
}
