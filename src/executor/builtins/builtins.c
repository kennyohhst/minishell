/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 23:15:01 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 01:25:33 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **argv)
{
	if (!strcmp(argv[0], "echo")
		|| (!strcmp(argv[0], "pwd")))
		// || (!strcmp(argv[0], "cd"))
		// || (!strcmp(argv[0], "env"))
		// || (!strcmp(argv[0], "export"))
		// || (!strcmp(argv[0], "unset")))
		return (true);
	return (false);
}


static int	execute_builtin(char **argv, t_envp *envp_list, int fd_out)
{
	char	*command;
	char	**envp;

	envp = envp_list_to_arr(envp_list);
	command = argv[0];
	if (!strcmp(command, "echo"))
		return (echo(argv, fd_out));
	if (!strcmp(argv[0], "pwd"))
		return (pwd(fd_out));
	// if (!strcmp(argv[0], "cd"))
	// 	return ();
	// if (!strcmp(argv[0], "env"))
	// 	return ();
	// if (!strcmp(argv[0], "export"))
	// 	return ();
	// if (!strcmp(argv[0], "unset"))
	// 	return ();
	return (0);
}

int	handle_builtin(t_command *cmd, t_envp *envp, int fd_in, int fd_out)
{
	int		ret;

	if (fd_in >= 0)
		close(fd_in);
	if (fd_out == -1)
		fd_out = STDOUT_FILENO;
	ret = execute_builtin(cmd->argv, envp, fd_out);
	if (ret == 0)
		cmd->pid = 0;
	else 
		cmd->pid = ret * -1;
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (1);
}