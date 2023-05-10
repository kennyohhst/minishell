/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 17:27:05 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/10 20:16:12 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_length(t_token *node)
{
	int		count;

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

void	sighandle_proc(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
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

static void	check_builtins(char **argv, char **envp)
{
	if (!ft_strncmp("echo", argv[0], 5))
		echo(argv);
	if (!ft_strncmp("pwd", argv[0], 4))
		pwd(argv);
	if (!ft_strncmp("pwd", argv[0], 4))
		env(argv, envp);
	if (!ft_strncmp("cd", argv[0], 4))
		cd(argv);
}

static int	child_process(t_token *cmd, char **envp)
{
	char		*path;
	char		**argv;

	argv = get_command_argv(cmd, list_length(cmd));
	if (!argv)
		exit (1);
	check_builtins(argv, envp);
	path = get_command_path(argv[0]);
	if (!path)
	{
		printf("%s -> Unknown command, maybe a built in?\n", argv[0]);
		free(argv[0]);
		exit (3);
	}
	return (execve(path, argv, envp));
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
