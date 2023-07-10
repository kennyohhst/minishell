/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/10 21:24:02 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include <fcntl.h>

t_redirect	*get_last_of_type(t_redirect *redirect, t_token_type type)
{
	t_redirect	*last;

	if (!redirect)
		return (NULL);
	last = NULL;
	while (redirect)
	{
		if (redirect->type == type)
			last = redirect;
		redirect = redirect->next;
	}
	return (last);
}

void	create_output_files(t_redirect *redirect)
{
	int		fd;

	while (redirect)
	{
		if (redirect->type == OUTPUT_REDIRECT)
		{
			fd = open(redirect->name, O_CREAT | O_WRONLY, 0644);
			if (fd == -1)
				return ;
			close(fd);
		}
		redirect = redirect->next;
	}
}

/**	
 * @brief Sets the fd field in redirect 
 * @return -1 for error, 0 if it's not the last node of this type, 1 for succes
*/
int	set_redirect_fd(t_redirect *redirect, t_token_type type)
{
	int		fd;

	fd = 0;
	if (!redirect)
	{
		if (type == INPUT_REDIRECT)
			fd = STDIN_FILENO;
		else if (type == OUTPUT_REDIRECT)
			fd = STDOUT_FILENO;
	}
	else if (type == INPUT_REDIRECT)
		fd = open(redirect->name, O_RDONLY);
	else if (type == OUTPUT_REDIRECT)
		fd = open(redirect->name, O_WRONLY);
	if (fd == -1)
	{
		perror(C_BOLD""C_RED"open error\n"C_RESET);
		return (-1);
	}
	redirect->fd = fd;
	return (1);
}

/*******************************************************************************
 * @brief	A function that dups the needed file descriptors 
 * 			onto STDIN and STDOUT
 * @param	pipe_fd		The file descriptors of the current pipe or 0 if there is none
 * @param	redirect	The redirect struct that contains the current fd and type
*******************************************************************************/
void	dup_to_standard_fd(int pipe_fd[2], t_redirect *redirect)
{
	if (redirect->type == INPUT_REDIRECT)
	{
		if (redirect->fd == STDIN_FILENO && pipe_fd)
			dup2(pipe_fd[0], STDIN_FILENO);
		else
			dup2(redirect->fd, STDIN_FILENO);
	}
	else if (redirect->type == OUTPUT_REDIRECT)
	{
		if (redirect->fd == STDOUT_FILENO && pipe_fd)
			dup2(pipe_fd[1], STDOUT_FILENO);
		else
			dup2(redirect->fd, STDOUT_FILENO);
	}
}

int	execute(t_command *cmd)
{
	t_redirect	*redirects;
	t_command	*current;
	t_redirect	*last[2];
	int			fd[2];

	while (current)
	{
		create_output_files(current->redirects);
		current = current->next;
	}

	last[0] = get_last_of_type(cmd->redirects, INPUT_REDIRECT);
	if (set_redirect_fd(last[0], INPUT_REDIRECT) == -1)
		return (-1);

	last[1] = get_last_of_type(cmd->redirects, OUTPUT_REDIRECT);
	if (set_redirect_fd(last[1], OUTPUT_REDIRECT) == -1)
		return (-1);

	if (!cmd->next)
	{
		dup_to_standard_fd(NULL, last[0]);
		dup_to_standard_fd(NULL, last[1]);
		return (1);
	}

	if (pipe(fd) == -1)
		return (-1);
	dup_to_standard_fd(fd, last[0]);
	dup_to_standard_fd(fd, last[1]);
	return (1);
}

int		main(void)
{
	t_command	*cmds;

	cmds = init_cmds();
	execute(cmds);

	return (0);
}
