/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 01:05:44 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int fd_out)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
	{
		perror("getcwd failed");
		return (1);
	}
	if (dprintf(fd_out, "%s\n", cwd) == -1)
		return (1);
	return (0);
}
