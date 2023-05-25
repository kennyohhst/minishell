/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 20:24:02 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/24 22:16:03 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp_list(t_envp *envp)
{
	while (envp)
	{
		printf("\e[0;31m%s:\e[0m\n", envp->str);
		printf("id : %s\t\tvalue : %s\n", envp->id, envp->value);
		envp = envp->next;
	}
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
