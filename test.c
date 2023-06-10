/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 21:40:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/06/11 01:21:09 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	orig;

void	execute_command(char **argv, int fd_in, int fd_out)
{
	int		pid;
	int		status;

	// printf("in: %d | out: %d\n", fd_in, fd_out);
	printf("started child process\noutput:\n");
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		if (fd_in >= 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out >= 0)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		execv(argv[0], argv);
		printf("execve error\n");
		exit(1);
	}
	waitpid(pid, &status, 0);
	printf("exit status: %d\n\n", status);
}

int		main(void)
{
	char	*argv1[3] = {"/bin/cat", "test.c", NULL};
	char	*argv2[3] = {"/usr/bin/wc", "-l", NULL};
	// char	*argv3[3] = {"/bin/cat", "-e", NULL};
	int		fd[2];
	int		pid;

	orig = dup(1);

	if (pipe(fd) == -1)
		exit(1);

	execute_command(argv1, -1, fd[1]);
	close(fd[1]);
	execute_command(argv2, fd[0], -1);

	close(fd[0]);

	dup2(orig, 1);
	close(orig);

	return (69);
}

