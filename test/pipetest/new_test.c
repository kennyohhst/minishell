/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/12 16:42:56 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include <fcntl.h>
#include "../../lib/libft/include/libft.h"

t_redirect	*get_last_node(t_redirect *redirect)
{
	while (redirect->next)
		redirect = redirect->next;
	return (redirect);
}

void	create_output_files(t_command *cmd)
{
	t_redirect	*output;
	int			fd;

	while (cmd)
	{
		output = cmd->output;
		while (output)
		{
			fd = open(output->name, O_CREAT | O_WRONLY, 0644);
			if (fd == -1)
				return ;
			close(fd);
			output = output->next;
		}
		cmd = cmd->next;
	}
}

/** @return A file descriptor to the created heredoc file or -1 on failure */
int		heredoc(char *delim)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		return (-1);

	write(STDOUT_FILENO, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	while (str && ft_strncmp(delim, str, ft_strlen(str) - 1))
	{
		write(fd[1], str, ft_strlen(str));
		free(str);
		write(STDOUT_FILENO, "> ", 2);
		str = get_next_line(STDIN_FILENO);
	}
	close (fd[1]);
	return (fd[0]);
}

/**	
 * @brief Sets the fd field in redirect 
 * @return -1 on error or 1 on succes
*/
int	set_redirect_fd(t_redirect *redirect)
{
	int				fd;
	t_token_type	type;

	fd = 0;
	type = redirect->type;
	if (type == INPUT_REDIRECT)
		fd = open(redirect->name, O_RDONLY);
	else if (type == HERE_DOC)
		fd = heredoc(redirect->name);
	else if (type == OUTPUT_REDIRECT)
		fd = open(redirect->name, O_WRONLY);
	else if (type == APPEND)
		fd = open(redirect->name, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror(C_BOLD""C_RED"open error\n"C_RESET);
		return (-1);
	}
	redirect->fd = fd;
	return (1);
}

void	close_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}

int run_command(char **argv, int fd_in, int fd_out)
{
	int		pid;
	int		status;

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
		return (-1);
	}
	close_pipe(fd_in, fd_out);
	waitpid(pid, &status, 0);
	return (status);
}

int	set_fds(t_command *cmd, int *fd_in, int *fd_out)
{
	t_redirect	*last_redirect;

	if (cmd->input)
	{
		close(*fd_in);
		last_redirect = get_last_node(cmd->input);
		if (set_redirect_fd(last_redirect) == -1)
			return (-1);
		*fd_in = last_redirect->fd;
	}
	if (cmd->output)
	{
		close(*fd_out);
		last_redirect = get_last_node(cmd->output);
		if (set_redirect_fd(last_redirect) == -1)
			return (-1);
		*fd_out = last_redirect->fd;
	}
	return (1);
}

int	execute(t_command *cmd)
{
	int fd_in;
	int new_pipe[2];

	create_output_files(cmd);
	fd_in = dup(STDIN_FILENO); // open new fd pointing to STDIN
	while (cmd->next)
	{
		if (pipe(new_pipe) == -1)
			return (-1);
		if (set_fds(cmd, &fd_in, &new_pipe[1]) == -1)
			return (-1);
		run_command(cmd->argv, fd_in, new_pipe[1]); // run command with fd_in being STDIN or the previous pipes read end and new pipes write end
		dup2(new_pipe[0], fd_in); // set fd_in to new pipes read end
		close(new_pipe[0]); // close new pipes read end
		cmd = cmd->next;
	}
	run_command(cmd->argv, fd_in, -1); // run command with the output going to STDOUT
	return (1);
}

int		main(void)
{
	t_command	*cmds;

	cmds = init_cmds();
	if (execute(cmds) == -1)
		return (1);
	return (0);
}
