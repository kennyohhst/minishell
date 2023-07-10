/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 21:40:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/10 20:29:56 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include <fcntl.h>

int	redirect(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->name, O_CREAT | O_WRONLY, 0770);
	if (fd == -1)
	{
		perror(C_BOLD""C_RED"open error\n"C_RESET);
		exit(2);
	}
	return (fd);
}

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

int	execute_command(char **argv, int fd_in, int fd_out)
{
	int			pid;
	int			status;
	static int	count = 1;

	printf(C_GREEN"started child process %d\n"C_RESET, count);
	printf(C_GREEN"in %d \t\t out %d\n"C_RESET, fd_in, fd_out);
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
	return (status);
}

void	pipe_loop(t_command *cmd)
{
	int		fd1[2];
	int		fd2[2];

	if (pipe(fd1) == -1)
		exit(1);

	dup2(STDIN_FILENO, fd1[0]);
	close(fd1[1]);
	while (cmd->next)
	{
		if (pipe(fd2) == -1)
			exit(1);
		if (cmd->redirects)
			dup2(redirect(cmd->redirects), fd2[1]);
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
	cmds->redirects = new_redirect_node("output.txt", OUTPUT_REDIRECT);
	pipe_loop(cmds);

	return (0);
}


/*
	make a function that gets the correct fds
	set correct fd in struct
	execute command
*/