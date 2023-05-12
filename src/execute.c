/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:27:05 by opelser           #+#    #+#             */
/*   Updated: 2023/05/12 18:32:18 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_length(t_token *node)
{
	int	count;

	if (!node)
		return (0);
	count = 0;
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}
// kenny why this??? >kenny did this because if you don't, 
// the ctrl+c after an empty "cat" will display "C Shell >> " 
// twice on the same line. this prevents that

void	sighandle_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sighandle_proc);
	}
}

static char	**get_command_argv(t_token *node, const int len)
{
	char		**argv;
	int			i;

	i = 0;
	if (!node)
		return (NULL);
	argv = malloc((len + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	while (node)
	{
		argv[i] = ft_strdup(node->str);
		node = node->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static int	child_process(t_token *cmd, char **envp)
{
	char		*cmd_path;
	char		**cmd_argv;

	cmd_argv = get_command_argv(cmd, list_length(cmd));
	if (!cmd_argv)
		exit (1);
	if (!ft_strncmp("echo", cmd_argv[0], 5))
		echo(cmd_argv);
	if (!ft_strncmp("pwd", cmd_argv[0], 4))
		pwd(cmd_argv);
	cmd_path = get_command_path(cmd_argv[0]);
	if (!cmd_path)
	{
		printf("%s -> Unknown command, maybe a built in?\n", cmd_argv[0]);
		free(cmd_argv[0]);
		exit (3);
	}
	return (execve(cmd_path, cmd_argv, envp));
}

int	execute(t_token *cmd, char **envp)
{
	pid_t	pid;

	signal(SIGINT, sighandle_proc);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (child_process(cmd, envp) == -1)
			return (0);
	}
	else
		wait(NULL);
	return (1);
}
