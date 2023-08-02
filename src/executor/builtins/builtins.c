/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 23:15:01 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/01 23:19:34 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **argv)
{
	if (!strcmp(argv[0], "echo")
		|| (!strcmp(argv[0], "pwd"))
		|| (!strcmp(argv[0], "env"))
		|| (!strcmp(argv[0], "cd"))
		|| (!strcmp(argv[0], "export"))
		|| (!strcmp(argv[0], "unset"))
		|| (!strcmp(argv[0], "exit")))
		return (true);
	return (false);
}

static int	execute_builtin(char **argv, t_data *data, int fd_out)
{
	char	*command;

	command = argv[0];
	if (!strcmp(command, "echo"))
		return (echo(argv, fd_out));
	if (!strcmp(command, "pwd"))
		return (pwd(fd_out));
	if (!strcmp(command, "env"))
		return (env(data->envp, fd_out));
	if (!strcmp(command, "cd"))
		return (cd(argv, data->envp));
	if (!strcmp(command, "export"))
		return (export(data, argv, fd_out));
	if (!strcmp(command, "unset"))
		return (unset(data, argv));
	if (!strcmp(command, "exit"))
		return (ft_exit(data, argv));
	return (0);
}

int	handle_builtin(t_command *cmd, t_data *data, int fd_in, int fd_out)
{
	int		ret;

	if (fd_in >= 0)
		close(fd_in);
	if (fd_out == -1)
		fd_out = STDOUT_FILENO;

	ret = execute_builtin(cmd->argv, data, fd_out);

	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (ret);
}