/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 20:09:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/02 15:33:02 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_envp *envp)
{
	char	*home;

	home = ft_getenv(envp, "HOME");
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

int	cd(char **argv, t_envp *envp)
{
	if (!argv[1])
		return (cd_home(envp));
	if (chdir(argv[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
