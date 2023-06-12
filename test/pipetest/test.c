/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 21:40:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/06/12 16:38:17 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

void	execute_command(char **argv, int fd_in, int fd_out)
{
	int			pid;
	int			status;
	static int	count = 1;

	printf(C_GREEN"started child process %d\n"C_RESET, count);
	printf(C_YELLOW"command: \"%s %s\"\n"C_RESET, argv[0], argv[1]);
	printf(C_CYAN"output"C_RESET"\n");
	count++;
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		if (fd_in >= 0)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out >= 0)
			dup2(fd_out, STDOUT_FILENO);
		close_pipe(fd_in, fd_out);
		execv(argv[0], argv);
		printf("execve error\n");
		exit(1);
	}
	close_pipe(fd_in, fd_out);
	waitpid(pid, &status, 0);
	printf(C_RED"exit status: %d\n\n"C_RESET, status);
}

void	pipe_loop(t_command *cmd)
{
	int		fd1[2];
	int		fd2[2];

	if (pipe(fd1) == -1)
		exit(1);

	execute_command(cmd->argv, -1, fd1[1]);
	cmd = cmd->next;
	while (cmd->next)
	{
		if (pipe(fd2) == -1)
			exit(1);
		execute_command(cmd->argv, fd1[0], fd2[1]);
		dup2(fd2[0], fd1[0]);
		close(fd2[0]);
		cmd = cmd->next;
	}
	execute_command(cmd->argv, fd1[0], -1);
}

int		main(void)
{
	t_command	*cmds;

	cmds = init_cmds();
	pipe_loop(cmds);

	return (0);
}

