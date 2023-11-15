/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:26:50 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 16:22:38 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_old(t_data *data, t_envp *prev, t_envp *old, t_envp *new)
{
	if (prev == NULL)
		data->envp = new;
	else
		prev->next = new;
	new->next = old->next;
	old->next = NULL;
	free_envp_list(old);
}

void	add_envp_node(t_data *data, t_envp *new)
{
	t_envp		*duplicate;
	t_envp		*prev;

	prev = NULL;
	duplicate = data->envp;
	while (duplicate && ft_strcmp(duplicate->id, new->id))
	{
		prev = duplicate;
		duplicate = duplicate->next;
	}
	if (duplicate)
	{
		if (duplicate->value && !new->value)
			free_envp_list(new);
		else
			replace_old(data, prev, duplicate, new);
	}
	else
	{
		if (data->envp)
			lst_add_back_envp(data->envp, new);
		else
			data->envp = new;
	}
}
