/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 22:37:25 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/25 21:30:50 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_back(t_envp *node, t_envp *new_node)
{
	if (!new_node)
		return ;
	while (node->next)
		node = node->next;
	node->next = new_node;
	new_node->prev = node;
}

bool	is_input_valid(t_envp *node)
{
	if (node->equal_index == 0)
	{
		free_envp_list(node);
		printf("not a valid identifier\n");
		return (false);
	}
	return (true);
}

t_envp	*check_duplicate(t_envp *head, t_envp *new_node)
{
	t_envp	*node;

	node = head;
	while (node)
	{
		if (!ft_strcmp(node->id, new_node->id))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	print_no_args(t_data *data)
{
	t_envp		*current;
	
	current = data->envp;
	while (current)
	{
		printf("declare -x %s", current->id);
		if (current->equal_index > 0)
			printf("=\"%s\'", current->value);
		printf("\n");
		current = current->next;
	}
}

void	add_node_to_envp_list(t_data *data, t_envp *new)
{
	t_envp	*old;

	old = check_duplicate(data->envp, new);
	if (!old)
	{
		lst_add_back(data->envp, new);
		return ;
	}
	if (old->prev)
	{
		old->prev->next = new;
		new->prev = old->prev;
	}
	else
		data->envp = new;
	if (old->next)
	{
		old->next->prev = new;
		new->next = old->next;
	}
	old->next = NULL;
	free_envp_list(old);
}

void	ft_export(t_data *data)
{
	int		i;
	t_envp	*new_node;

	if (!data->command->argv[1])
	{
		print_no_args(data);
		return ;
	}

	i = 1;
	while (data->command->argv[i])
	{
		new_node = create_new_envp_node(data->command->argv[i]);
		if (!new_node)
		{
			printf("create new envp node returned (null)\n");
			return ;
		}
		if (is_input_valid(new_node) == true)
			add_node_to_envp_list(data, new_node);
		i++;
	}
}
