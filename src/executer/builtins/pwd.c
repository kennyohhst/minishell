/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:55 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/25 22:49:25 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	cwd[256];

	if (!getcwd(cwd, 256))
	{
		perror("getcwd failed");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
