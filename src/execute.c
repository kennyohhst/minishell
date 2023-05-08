/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 17:27:05 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/08 17:23:09 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		list_length(t_token *node)
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
		return (2);

	cmd_path = get_command_path(cmd_argv[0]);
	if (!cmd_path)
	{
		// check for and execute built ins
		printf("Unknown command, maybe a built in?\n");
		ft_free_str_arr(cmd_argv);
		return (1);
	}

	exit (execve(cmd_path, cmd_argv, envp));
}

int	execute(t_token *cmd, char **envp)
{
	pid_t	pid;

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
