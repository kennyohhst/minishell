/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:15:01 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 16:21:03 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **argv)
{
	if (!argv || !argv[0])
		return (false);
	if (!ft_strcmp(argv[0], "echo")
		|| (!ft_strcmp(argv[0], "pwd"))
		|| (!ft_strcmp(argv[0], "env"))
		|| (!ft_strcmp(argv[0], "cd"))
		|| (!ft_strcmp(argv[0], "export"))
		|| (!ft_strcmp(argv[0], "unset"))
		|| (!ft_strcmp(argv[0], "exit")))
		return (true);
	return (false);
}

static int	execute_builtin(char **argv, t_data *data, int fd_out)
{
	char	*command;

	command = argv[0];
	if (!ft_strcmp(command, "echo"))
		return (echo(argv, fd_out));
	if (!ft_strcmp(command, "pwd"))
		return (pwd(fd_out));
	if (!ft_strcmp(command, "env"))
		return (env(data->envp, fd_out));
	if (!ft_strcmp(command, "cd"))
		return (cd(data, argv));
	if (!ft_strcmp(command, "export"))
		return (export(data, argv, fd_out));
	if (!ft_strcmp(command, "unset"))
		return (unset(data, argv));
	if (!ft_strcmp(command, "exit"))
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
