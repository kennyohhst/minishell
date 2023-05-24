/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 22:37:25 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/24 18:43:27 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_envp_list(t_envp *node)
{
	node->next = NULL;
	free_envp_list(node);
}

void	lst_add_back(t_envp *node, t_envp *new_node)
{
	if (!new_node)
		return ;
	while (node->next)
		node = node->next;
	node->next = new_node;
	new_node->prev = node;
}

void	insert_in_envp_list(t_envp *node, t_envp *new_node)
{
	new_node->next = node->next;
	node->next = new_node;
	new_node->prev = node;
}

t_envp	*check_node(t_envp *head, t_envp *new_node)
{
	t_envp	*node;

	node = head;
	if (new_node->equal_index == 0)
	{
		//handle wrong input
		new_node->prev->next = NULL;
		free_envp_list(new_node);
		printf("not a valid identifier\n");
		return (NULL);
	}
	while (node)
	{
		if (!ft_strcmp(node->id, new_node->id))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	print_no_args(t_program_data *data)
{
	t_envp		*current;
	
	current = data->envp;
	while (current)
	{
		write(1, "declare -x ", 12);
		write(1, current->id, ft_strlen(current->id));
		if (current->equal_index > 0)
		{
			write(1, "=\"", 2);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		current = current->next;
	}
}

t_envp	*get_head(t_envp	*node_in_list)
{
	while (node_in_list->prev)
		node_in_list = node_in_list->prev;
	return (node_in_list);
}

void	export(t_program_data *data)
{
	int		i;
	t_envp	*new_node;
	t_envp	*tmp;

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
			// handle null return
			printf("create new envp node returned (null)\n");
			return ;
		}
		tmp = check_node(data->envp, new_node);
		if (!tmp)
			lst_add_back(data->envp, new_node); // what if fails check
		else
		{
			if (!tmp->prev)
				data->envp = new_node;
			else
			{
				tmp->prev->next = new_node;
				new_node->prev = tmp->prev;
			}
			if (!tmp->next)
				new_node->next = NULL;
			else
			{
				tmp->next->prev = new_node;
				new_node->next = tmp->next;
			}
			remove_from_envp_list(tmp);
		}
		i++;
	}
}
