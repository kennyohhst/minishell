/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 20:09:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/21 23:51:44 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	write(1, home, ft_strlen(home));
	write(1, "\n", 1);
	if (chdir(home) == -1)
		return (2);
	return (0);
}

int		cd(char **argv)	// export new cwd and old cwd
{
	char	cwd[1024];
	int		arg_len;

	if (!argv[1])
		return (cd_home());
	if (chdir(argv[1]) == 0)
		return (1);
	arg_len = ft_strlen(argv[1]);
	if (arg_len >= 1024)
	{
		perror("cd error -> File name too long\n");
		return (0);
	}
	if (!getcwd(cwd, 256))
		return (0);
	// export(OLDPWD=cwd);
	ft_strcat(cwd, "/");
	ft_strcat(cwd, argv[1]);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	if (chdir(cwd) == -1)
		return (0);
	ft_free_str_arr(argv);
	return (1);
}
