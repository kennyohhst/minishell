/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:27:05 by opelser           #+#    #+#             */
/*   Updated: 2023/05/20 17:50:23 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandle_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sighandle_proc);
	}
}

static void	check_builtins(char **argv, char **envp)
{
	if (!ft_strncmp("echo", argv[0], 5))
		echo(argv);
	if (!ft_strncmp("pwd", argv[0], 4))
		pwd(argv);
	if (!ft_strncmp("env", argv[0], 4))
		env(argv, envp);
	if (!ft_strncmp("cd", argv[0], 3))
		exit (cd(argv));
}

static int	child_process(char **argv, char **envp)
{
	char		*path;

	check_builtins(argv, envp);
	path = get_command_path(argv[0]);
	if (!path)
	{
		printf("%s -> Unknown command, maybe a built in?\n", argv[0]);
		ft_free_str_arr(argv);
		exit (3);
	}
	return (execve(path, argv, envp));
}

static void	ft_free_command_list(t_command **cmd)
{
	t_command	*next;

	next = (*cmd)->next;
	ft_free_str_arr((*cmd)->argv);
	// free redirects
	free(*cmd);
	*cmd = next;
}

int	execute(t_program_data *data, t_command **cmd)
{
	pid_t	pid;

	// for (int i = 0; argv[i]; i++)
		// printf("argv[%d] = [%s]\n", i, argv[i]);
	signal(SIGINT, sighandle_proc);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (child_process((*cmd)->argv, data->envp) == -1)
			return (0);
	}
	else
		wait(NULL);
	ft_free_command_list(cmd);
	return (1);
}
