/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:21:29 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 15:46:46 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	id_check(t_data *data, char *str)
{
	t_envp		*node;
	t_envp		*prev;

	prev = NULL;
	node = data->envp;
	while (node)
	{
		if (!ft_strcmp(str, node->id))
		{
			if (node == data->envp)
				data->envp = node->next;
			if (prev)
				prev->next = node->next;
			node->next = NULL;
			free_envp_list(node);
			return ;
		}
		prev = node;
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
