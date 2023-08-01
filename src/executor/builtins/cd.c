/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 20:09:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 16:19:26 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_envp *envp)
{
	char	*home;

	home = ft_getenv(envp, "HOME");		// get home from my envp list
	if (!home)
	{
		dprintf(STDERR_FILENO, "minishell: cd: HOME not set");
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int		cd(char **argv, t_envp *envp)	// export new cwd and old cwd
{
	char	cwd[1024];

	if (!argv[1])
		return (cd_home(envp));
	if (!getcwd(cwd, 256))
		return (1);
	// export OLDPWD=cwd
	ft_strcat(cwd, "/");
	ft_strcat(cwd, argv[1]);
	if (chdir(cwd) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	// export(PWD=cwd);
	return (0);
}
