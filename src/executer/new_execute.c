/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_execute.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 21:40:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/06/14 23:30:18 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	sighandle_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sighandle_proc);
	}
}

static void	ft_free_current_command(t_data *data)
{
	t_command	*next;

	next = data->command->next;
	ft_free_str_arr(data->command->argv);
	free(data->command);
	data->command = next;
}

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

int	execute_command(char **argv, char **envp, int fd_in, int fd_out)
{
	int			pid;
	int			status;
	char		*path;
	static int	count = 1;

	printf(C_GREEN"in %d \t\t out %d\n"C_RESET, fd_in, fd_out);
	printf(C_GREEN"started child process %d\n"C_RESET, count);
	printf(C_YELLOW"command: \"%s %s\"\n"C_RESET, argv[0], argv[1]);
	printf(C_CYAN"output"C_RESET"\n");
	count++;

	path = get_command_path(argv[0]);
	if (!path)
	{
		printf("minishell -> %s -> command not found\n", argv[0]);
		return (127);
	}
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
		execve(path, argv, envp);
		printf("execve error\n");
		exit(1);
	}
	close_pipe(fd_in, fd_out);
	waitpid(pid, &status, 0);
	printf(C_RED"exit status: %d\n\n"C_RESET, status);
	return (status);
}

void	pipe_loop(t_data *data)
{
	char		**envp;
	int			fd1[2];
	int			fd2[2];

	if (pipe(fd1) == -1)
		exit(1);

	envp = envp_list_to_arr(data->envp);
	if (!envp)
		exit(1);
	dup2(STDIN_FILENO, fd1[0]);
	close(fd1[1]);
	while (data->command && data->command->next)
	{
		if (pipe(fd2) == -1)
			exit(1);
		execute_command(data->command->argv, envp, fd1[0], fd2[1]);
		dup2(fd2[0], fd1[0]);
		close(fd2[0]);
		ft_free_current_command(data);
	}
	if (data->command)
		execute_command(data->command->argv, envp, fd1[0], -1);
}

int	execute(t_data *data)
{
	signal(SIGINT, sighandle_proc);
	pipe_loop(data);
	return (1);
}


