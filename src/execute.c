/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 17:27:05 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/08 15:18:20 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(char *cmd, char **argv, char **envp)
{
	exit (execve(cmd, argv, envp));
}

int	execute(char *command_path, char **argv, char **envp)
{
	pid_t	pid;

	if (!command_path)
	{
		// execute built ins
		printf("not worked on this yet\n");
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (child_process(command_path, argv, envp) == -1)
			return (0);
	}
	else
		wait(NULL);
	return (1);
}
