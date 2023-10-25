/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 15:43:03 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 18:09:54 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

#define USE_STANDARD_FD -1

void	close_fds(int fd_in, int fd_out)
{
	if (fd_in != USE_STANDARD_FD)
		close(fd_in);
	if (fd_out != USE_STANDARD_FD)
		close(fd_out);
}

void	set_fds(int *fd_in, int *fd_out)
{
	if (*fd_in != USE_STANDARD_FD)
	{
		if (dup2(*fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
	}
	if (*fd_out != USE_STANDARD_FD)
	{
		if (dup2(*fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
	}
}

static bool	is_dir(char *arg)
{
	struct stat		path_stat;

	if (stat(arg, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode) == true)
		return (true);
	return (false);
}

void	execve_error(char *arg)
{
	if (errno == EACCES)
	{
		if (is_dir(arg) == true)
			print_error(NULL, arg, "Is a directory");
		else
			print_error(NULL, arg, "Permission denied");
		exit(126);
	}
	else
	{
		perror(arg);
		exit(127);
	}
}
