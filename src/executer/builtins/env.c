/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:00:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/24 23:17:25 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_envp *envp)
{
	while (envp)
	{
		if (envp->equal_index > 0)
		{
			write(1, envp->str, ft_strlen(envp->str));
			write(1, "\n", 1);
		}
		envp = envp->next;
	}
}
