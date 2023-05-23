/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/20 21:31:34 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **argv)
{
	char	cwd[256];

	ft_free_str_arr(argv);
	if (!getcwd(cwd, 256))
	{
		perror("getcwd failed");
		return (1);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}
