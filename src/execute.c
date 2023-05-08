/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:27:05 by opelser           #+#    #+#             */
/*   Updated: 2023/05/06 20:25:50 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(char *cmd, char **argv, char **envp)
{
	exit (execve(cmd, argv, envp));
}

void	sighandle_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sighandle_proc);
	}
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
	signal(SIGINT, sighandle_proc);
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (child_process(command_path, argv, envp) == -1)
			return (0);
	}
	else
		wait(&pid);
	return (1);
}
