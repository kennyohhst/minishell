/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 20:26:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/11 19:39:05 by opelser       ########   odam.nl         */
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

void	create_output_files(t_command *cmd)
{
	t_redirect	*output;
	int		fd;

	while (cmd)
	{
		output = cmd->output;
		while (output)
		{
			if (output->type == OUTPUT_REDIRECT)
			{
				fd = open(output->name, O_CREAT | O_WRONLY, 0644);
				if (fd == -1)
					return ;
				close(fd);
			}
			output = output->next;
		}
		cmd = cmd->next;
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

int	handle_redirects(t_command *cmd)
{
	t_redirect	*input;
	t_redirect	*output;

	input = get_last_of_type(cmd->input, INPUT_REDIRECT);
	if (set_redirect_fd(input, INPUT_REDIRECT) == -1)
		return (-1);

	output = get_last_of_type(cmd->output, OUTPUT_REDIRECT);
	if (set_redirect_fd(output, OUTPUT_REDIRECT) == -1)
		return (-1);
	return (1);
}

int	execute(t_command *cmd)
{
	// set up pipes

	create_output_files(cmd);
	handle_redirects(cmd);
	if (!cmd->next)
	{
		dup_to_standard_fd(NULL, get_last_of_type(cmd->input, INPUT_REDIRECT));
		dup_to_standard_fd(NULL, get_last_of_type(cmd->output, OUTPUT_REDIRECT));
		execv(cmd->argv[0], cmd->argv);
		return (1);
	}
	return (1);
}

int		main(void)
{
	t_command	*cmds;

	cmds = init_cmds();
	cmds->next = NULL;
	execute(cmds);

	return (0);
}
