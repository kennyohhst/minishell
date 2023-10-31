/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 20:09:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 14:55:53 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to update oldpwd and pwd

static int	cd_oldpwd(t_envp *envp)
{
	char	*old_pwd;

	old_pwd = ft_getenv(envp, "OLDPWD");
	if (!old_pwd)
	{
		print_error("cd", NULL, "OLDPWD not set");
		return (1);
	}
	if (chdir(old_pwd) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

static int	cd_home(t_envp *envp)
{
	char	*home;

	home = ft_getenv(envp, "HOME");
	if (!home)
	{
		print_error("cd", NULL, "HOME not set");
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	cd(char **argv, t_envp *envp)
{
	if (!argv[1])
		return (cd_home(envp));
	if (argv[2])
	{
		print_error("cd", NULL, "too many arguments");
		return (1);
	}
	if (ft_strcmp(argv[1], "~") == 0)
		return (cd_home(envp));
	if (ft_strcmp(argv[1], "-") == 0)
		return (cd_oldpwd(envp));
	if (chdir(argv[1]) == -1)
	{
		print_error("cd", strerror(errno), argv[1]);
		return (1);
	}
	return (0);
}
