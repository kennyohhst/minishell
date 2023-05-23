/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 20:24:02 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/23 21:19:17 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		envp_list_size(t_envp *envp)
{
	int		count;

	count = 0;
	while (envp)
	{
		count++;
		envp = envp->next;
	}
	return (count);
}

char	**envp_list_to_arr(t_envp *envp)
{
	int		len;
	int		i;
	char	**char_envp;

	len = envp_list_size(envp);
	char_envp = (char **) malloc((len + 1) * sizeof(char *));

	i = 0;
	while (envp)
	{
		char_envp[i] = envp->str;
		envp = envp->next;
		i++;
	}
	char_envp[i] = NULL;
	return (char_envp);
}
