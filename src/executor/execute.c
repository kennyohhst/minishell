/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/27 15:27:18 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/errno.h>

int	g_exit;

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

pid_t run_command(char **argv, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (fd_in >= 0)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out >= 0)
			dup2(fd_out, STDOUT_FILENO);
		close_pipe(fd_in, fd_out);
		execv(argv[0], argv);
		perror(argv[0]);
		close_pipe(fd_in, fd_out);
		exit(errno);
	}
	close_pipe(fd_in, fd_out);
	return (pid);
}

int	execute(t_command *cmd, t_envp *envp_list)
{
	char	*path;
	int		fd_in;
	int		new_pipe[2];

	path = get_command_path(cmd->argv[0], envp_list);
	if (!path)
	{
		dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv[0]);
		return (-1);
	}
	free(cmd->argv[0]);
	cmd->argv[0] = path;
	printf("path = %s\n", path);
	create_output_files(cmd);
	fd_in = dup(STDIN_FILENO); // open new fd pointing to STDIN
	while (cmd->next)
	{
		if (pipe(new_pipe) == -1)
			return (-1);
		if (handle_redirects(cmd, &fd_in, &new_pipe[1]) == -1)
			return (-1);
		cmd->pid = run_command(cmd->argv, fd_in, new_pipe[1]); // run command with fd_in being STDIN or the previous pipes read end and new pipes write end
		fd_in = dup(new_pipe[0]); // set fd_in to new pipes read end
		close(new_pipe[0]); // close new pipes read end
		cmd = cmd->next;
	}
	run_command(cmd->argv, fd_in, -1); // run command with the output going to STDOUT
	return (1);
}
