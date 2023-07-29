/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 23:15:01 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 00:27:02 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **argv)
{
	if (!strcmp(argv[0], "echo"))
		// || (!strcmp(argv[0], "cd"))
		// || (!strcmp(argv[0], "pwd"))
		// || (!strcmp(argv[0], "env"))
		// || (!strcmp(argv[0], "export"))
		// || (!strcmp(argv[0], "unset")))
		return (true);
	return (false);
}

static int	reset_fds(int in_orig, int out_orig)
{
	if (dup2(in_orig, STDIN_FILENO) == -1)
	{
		dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_in\n");
		return (-1);
	}
	if (dup2(out_orig, STDOUT_FILENO) == -1)
	{
		dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_out\n");
		return (-1);
	}
	close_fds(in_orig, out_orig);
	return (1);
}


static int	set_temporary_fds(int fd_in, int fd_out, int *in_orig, int *out_orig)
{
	*out_orig = -1;
	*in_orig = dup(STDIN_FILENO);
	if (*in_orig == -1)
	{
		dprintf(STDERR_FILENO, "Error setting temporary STDIN for builtin");
		return (-1);
	}
	*out_orig = dup(STDOUT_FILENO);
	if (*out_orig == -1)
	{
		dprintf(STDERR_FILENO, "Error setting temporary STDOUT for builtin");
		return (-1);
	}
	if (fd_in >= 0 && dup2(fd_in, STDIN_FILENO) == -1)
	{
		dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_in\n");
		return (-1);
	}
	if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) == -1)
	{
		dprintf(STDERR_FILENO, "minishell: dup2 failed to set fd_out\n");
		return (-1);
	}
	close_fds(fd_in, fd_out);
	return (1);
}


static int	execute_builtin(char **argv, t_envp *envp_list)
{
	char	*command;
	char	**envp;

	envp = envp_list_to_arr(envp_list);
	command = argv[0];
	if (!strcmp(command, "echo"))
		return (echo(argv));
	// if (!strcmp(argv[0], "cd"))
	// 	return ();
	// if (!strcmp(argv[0], "pwd"))
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
	int		stdin_orig;
	int		stdout_orig;

	if (set_temporary_fds(fd_in, fd_out, &stdin_orig, &stdout_orig) == -1)
	{
		close_fds(stdin_orig, stdout_orig);
		return (-1);
	}
	cmd->pid = execute_builtin(cmd->argv, envp);
	if (reset_fds(stdin_orig, stdout_orig) == -1)
		return (-1);
	return (1);
}