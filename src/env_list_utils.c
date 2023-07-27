/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 20:24:02 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/26 22:21:01 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_envp *envp_list, char *id)
{
	if (!id)
		return (NULL);
	while (envp_list)
	{
		if (!ft_strcmp(id, envp_list->id))
			return (envp_list->value);
		envp_list = envp_list->next;
	}
	return (NULL);
}

void	*free_envp_list(t_envp *node)
{
	t_envp	*next;

	while (node)
	{
		next = node->next;
		if (node->str)
			free(node->str);
		if (node->id)
			free(node->id);
		if (node->value)
			free(node->value);
		free(node);
		node = next;
	}
	return (NULL);
}

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
