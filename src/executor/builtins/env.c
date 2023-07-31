/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:00:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 17:56:25 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_envp *envp, int fd_out)
{
	while (envp)
	{
		if (envp->value && dprintf(fd_out, "%s\n", envp->str) == -1)
			return (1);
		envp = envp->next;
	}
	return (0);
}
