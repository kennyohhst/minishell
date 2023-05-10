/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 20:09:42 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/10 20:36:40 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv)		// split up cwd and new cwd, add error returns, cant take directories bigger than 512					EXECUTES IN CHILD PROCESS
{
	char	cwd[256];
	char	new_cwd[512];
	int		arg_len;

	arg_len = ft_strlen(argv[1]);
	if (arg_len >= 255)
	{
		perror("directory too long");
		exit (1);
	}
	if (!getcwd(cwd, 256))
	{
		perror("getcwd failed");
		exit (2);
	}
	ft_strlcat(cwd, "/", ft_strlen(cwd) + 2);
	ft_strlcat(cwd, argv[1], ft_strlen(cwd) + arg_len + 1);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	if (chdir(cwd) == -1)
		write(1, "it fucked up\n", 15);
	ft_free_str_arr(argv);
	exit (0);
}