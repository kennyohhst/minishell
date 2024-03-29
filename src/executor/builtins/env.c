/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:00:00 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 15:16:28 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_envp *envp, int fd_out)
{
	while (envp)
	{
		if (envp->value)
		{
			if (write(fd_out, envp->str, ft_strlen(envp->str)) == -1)
				return (1);
			if (write(fd_out, "\n", 1) == -1)
				return (1);
		}
		envp = envp->next;
	}
	return (0);
}
