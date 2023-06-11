/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 21:40:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/06/11 16:38:44 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

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
			dup2(fd_in, STDIN_FILENO);
		if (fd_out >= 0)
			dup2(fd_out, STDOUT_FILENO);
		close_if_valid(fd_in);
		close_if_valid(fd_out);
		execv(argv[0], argv);
		printf("execve error\n");
		exit(1);
	}
	close_if_valid(fd_in);
	close_if_valid(fd_out);
	waitpid(pid, &status, 0);
	printf("exit status: %d\n\n", status);
}

int		main(void)
{
	char	*argv1[3] = {"/bin/cat", "test.c", NULL};
	char	*argv2[3] = {"/usr/bin/wc", "-l", NULL};
	char	*argv3[3] = {"/bin/cat", "-e", NULL};
	char	**argvs[4] = {argv1, argv2, argv3, NULL};
	int		fd[2];
	int		fd2[2];
	int		pid;
	int		i = 1;

	if (pipe(fd) == -1)
		exit(1);
	if (pipe(fd2) == -1)
		exit(1);

	execute_command(argvs[0], -1, fd[1]);
	while(argvs[i + 1])
	{
		execute_command(argvs[i], fd[0], fd2[1]);
		i++;
	}
	execute_command(argvs[i], fd2[0], -1);

	return (69);
}

