/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 23:21:29 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/31 19:03:21 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	id_check(t_data *data, char *str)
{
	t_envp		*node;

	node = data->envp;
	while (node)
	{
		if (!ft_strcmp(str, node->id))
		{
			if (node->prev)
				node->prev->next = node->next;
			else
				data->envp = node->next;
			if (node->next)
				node->next->prev = node->prev;
			node->next = NULL;
			free_envp_list(node);
			return ;
		}
		node = node->next;
	}
}

int	unset(t_data *data, char **argv)
{
	int			i;

	i = 1;
	while (argv[i])
	{
		id_check(data, argv[i]);
		i++;
	}
	return (0);
}
