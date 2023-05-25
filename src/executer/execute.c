/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 17:27:05 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/25 22:51:00 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	sighandle_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sighandle_proc);
	}
}

static void	ft_free_current_command(t_data *data)
{
	t_command	*next;

	next = data->command->next;
	ft_free_str_arr(data->command->argv);
	// free redirects
	free(data->command);
	data->command = next;
}

static bool	is_builtin(t_data *data)
{
	char	**argv;

	argv = data->command->argv;
	if (!ft_strncmp("exit", argv[0], 5))
		exit(0);
	else if (!ft_strncmp("echo", argv[0], 5))
		return (echo(argv), true);
	else if (!ft_strncmp("pwd", argv[0], 4))
		return (pwd(), true);
	else if (!ft_strncmp("env", argv[0], 4))
		return (env(data->envp), true);
	else if (!ft_strncmp("cd", argv[0], 3))		// not returning correctly yet
		return (cd(argv), true);
	else if (!ft_strncmp("export", argv[0], 8))
		return (ft_export(data), true);
	else if (!ft_strncmp("unset", argv[0], 6))
		return (unset(data), true);
	return (false);
}

static int	execute_in_child(t_data *data)
{
	char	**argv;
	char	**envp;
	char	*path;

	envp = envp_list_to_arr(data->envp);
	if (!envp)
		exit(1);
	argv = data->command->argv;

	if (is_builtin(data) == true)
	{
		ft_free_current_command(data);
		exit(errno);
	}
	path = get_command_path(argv[0]);
	if (!path)
	{
		printf("%s -> command not found\n", argv[0]);
		exit (3);
	}
	return (execve(path, argv, envp));
}

int	execute(t_data *data)
{
	pid_t			pid;
	t_command		*cmd;

	cmd = data->command;
	signal(SIGINT, sighandle_proc);

	if (!ft_strncmp("?", cmd->argv[0], 2))
		return (printf("%d\n", data->exit_code));

	if (!cmd->redirects && is_builtin(data) == true)
	{
		ft_free_current_command(data);
		return (0);
	}

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		execute_in_child(data);			// make sure child processes free all
	else
		waitpid(pid, &data->exit_code, 0);
	ft_free_current_command(data);
	return (1);
}
