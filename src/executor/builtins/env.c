/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:00:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/29 20:30:53 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_envp *envp)
{
	while (envp)
	{
		if (envp->equal > 0)
			printf("%s\n", envp->str);
		envp = envp->next;
	}
}
