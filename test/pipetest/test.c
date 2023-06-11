/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 21:40:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/06/12 01:17:46 by opelser       ########   odam.nl         */
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

	printf("started child process %d\noutput:\n", count);
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
	printf("exit status: %d\n\n", status);
}

int		main(void)
{
	t_command	*cmds;
	int		fd[2];
	int		fd2[2];

	cmds = init_cmds();

	if (pipe(fd) == -1)
		exit(1);
	if (pipe(fd2) == -1)
		exit(1);

	execute_command(cmds->argv, -1, fd[1]);
	cmds = cmds->next;
	while(cmds->next)
	{
		execute_command(cmds->argv, fd[0], fd2[1]);
		cmds = cmds->next;
	}
	execute_command(cmds->argv, fd2[0], -1);

	return (0);
}

