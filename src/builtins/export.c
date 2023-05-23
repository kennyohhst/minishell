/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 22:37:25 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/24 01:22:13 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_envp_list(t_envp *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->next = NULL;
	free_envp_list(node);
}

t_envp	*is_duplicate(t_envp *head, t_envp *new_node)
{
	t_envp	*node;

	node = head;
	while (node->next)
	{
		if (!ft_strcmp(node->id, new_node->id))
		{
			remove_from_envp_list(node);
			node = head;
		}
		node = node->next;
	}
	node->next = new_node;
	return (new_node);
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

void	export(t_program_data *data)
{
	int		i;
	t_envp	*last_node;
	t_envp	*tmp;

	if (!data->command->argv[1])
	{
		print_no_args(data);
		return ;
	}

	last_node = data->envp;
	while (last_node && last_node->next)
		last_node = last_node->next;

	i = 1;
	while (data->command->argv[i])
	{
		tmp = create_new_envp_node(data->command->argv[i]);
		if (!tmp)
		{
			// handle null return
			printf("create new envp node returned (null)\n");
			return ;
		}
		last_node = is_duplicate(data->envp, tmp);
		if (last_node->equal_index == 0)
		{
			//handle wrong input
			printf("not a valid identifier\n");
			return ;
		}
		i++;
	}
}
