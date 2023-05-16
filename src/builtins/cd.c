/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 20:09:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/16 20:51:54 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	write(1, home, ft_strlen(home));
	write(1, "\n", 1);
	if (chdir(home) == -1)
		return (3);
	return (0);
}

static int	cd_oldpwd(void)
{
	char	*old_pwd;

	old_pwd = getenv("OLDPWD");
	if (!old_pwd)
	{
		write(1, old_pwd, ft_strlen(old_pwd));
		write(1, "\n", 1);
		perror("cd error -> OLDPWD not set\n");
		return (-1);
	}
	if (chdir(old_pwd) == -1)
		return (3);
	return (0);
}

int		cd(char **argv)		// split up cwd and new cwd, add error returns, cant take directories bigger than 512					EXECUTES IN CHILD PROCESS
{
	char	cwd[256];
	int		arg_len;

	if (!argv[1] || !ft_strncmp("~", argv[1], 2))
		return (cd_home());
	if (!ft_strncmp("-", argv[1], 2))
		return (cd_oldpwd());
	arg_len = ft_strlen(argv[1]);
	if (arg_len >= 255)
	{
		perror("cd error -> File name too long\n");
		return (-1);
	}
	if (!getcwd(cwd, 256))
		return (-1);
	// export(OLDPWD=cwd);
	ft_strcat(cwd, "/");
	ft_strcat(cwd, argv[1]);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	if (chdir(cwd) == -1)
		return (-1);
	ft_free_str_arr(argv);
	return (0);
}
