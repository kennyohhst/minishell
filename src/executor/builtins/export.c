/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 22:37:25 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/31 16:52:23 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_add_back(t_envp *node, t_envp *new_node)
{
	if (!new_node)
		return ;
	while (node->next)
		node = node->next;
	node->next = new_node;
	new_node->prev = node;
}

static bool	is_valid_id(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha((int) str[i]))
		{
			dprintf(STDERR_FILENO, "minishell: export: '%s': not a valid identifier\n", str);
			return (false);
		}
		i++;
	} 
	return (true);
}

void	print_no_args(t_data *data, int fd_out)
{
	t_envp		*current;
	
	current = data->envp;
	while (current)
	{
		dprintf(fd_out, "declare -x %s", current->id);
		if (current->value)
			dprintf(fd_out, "=\"%s\"", current->value);
		dprintf(fd_out, "\n");
		current = current->next;
	}
}

static void	replace_old(t_data *data, t_envp *old, t_envp *new)
{
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

static int	add_node(t_data *data, t_envp *new)
{
	t_envp		*duplicate;

	duplicate = data->envp;
	while (duplicate)
	{
		if (!ft_strcmp(duplicate->id, new->id))
			break ;
		duplicate = duplicate->next;
	}
	if (duplicate)
	{
		if (duplicate->value && !new->value)
			free_envp_list(new);
		else
			replace_old(data, duplicate, new);
	}
	else
	{
		if (data->envp)
			lst_add_back(data->envp, new);
		else
			data->envp = new;
	}
	return (1);
}

int	export(t_data *data, char **argv, int fd_out)
{
	t_envp	*new;
	int		ret;
	int		i;

	ret = 0;
	if (!argv[1])
	{
		print_no_args(data, fd_out);
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		new = create_new_envp_node(argv[i]);
		if (!new)
			return (1);
		if (is_valid_id(new->str) == false)
			ret = 1;
		else if (add_node(data, new) == -1)
			ret = 1;
		i++;
	}
	return (ret);
}
