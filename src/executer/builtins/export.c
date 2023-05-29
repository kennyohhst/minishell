/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 22:37:25 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/29 22:07:17 by opelser       ########   odam.nl         */
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

void	concat_value_if_plus(t_envp *new, t_envp *old)
{
	char	*tmp;

	if (new->plus <= 0 || !old)
		return ;
	tmp = ft_strjoin(old->value, new->value);
	free(new->value);
	new->value = tmp;
}

bool	is_input_valid(t_envp *old, t_envp *new)
{
	int		i;

	if (new->equal == 0)
	{
		printf("export: '%s': not a valid identifier\n", new->str);
		return (false);
	}
	i = 0;
	while (new->id[i])
	{
		if (!ft_isalpha((int) new->id[i]))
		{
			printf("export: '%s': not a valid identifier\n", new->str);
			return (false);
		}
		i++;
	}
	if (old && (old->value && !new->value))
		return (false);
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
		if (current->equal > 0)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	add_node_to_envp_list(t_data *data, t_envp *old, t_envp *new)
{
	if (!old)
	{
		lst_add_back(data->envp, new);
		return ;
	}
	if (old->prev)
		old->prev->next = new;
	else
		data->envp = new;
	if (old->next)
		old->next->prev = new;
	new->prev = old->prev;
	new->next = old->next;
	old->next = NULL;
	free_envp_list(old);
}

void	ft_export(t_data *data)
{
	int		i;
	t_envp	*new;
	t_envp	*old;

	if (!data->command->argv[1])
	{
		print_no_args(data);
		return ;
	}

	i = 1;
	while (data->command->argv[i])
	{
		new = create_new_envp_node(data->command->argv[i]);
		if (!new)
		{
			printf("create new envp node returned (null)\n");
			return ;
		}
		old = check_duplicate(data->envp, new);
		concat_value_if_plus(new, old);
		if (is_input_valid(old, new) == true)
			add_node_to_envp_list(data, old, new);
		else
			free_envp_list(new);
		i++;
	}
}
