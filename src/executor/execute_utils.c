/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 15:43:03 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 15:57:28 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
