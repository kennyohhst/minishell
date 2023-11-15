/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:37:25 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 15:01:22 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_id(char *str)
{
	int		i;

	if (!str)
	{
		print_error("export", "=", "not a valid identifier");
		return (false);
	}
	if (!ft_isalpha((int) str[0]))
	{
		print_error("export", str, "not a valid identifier");
		return (false);
	}
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum((int) str[i]))
		{
			print_error("export", str, "not a valid identifier");
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
		write(fd_out, "declare -x ", 11);
		write(fd_out, current->id, ft_strlen(current->id));
		if (current->value)
		{
			write(fd_out, "=\"", 2);
			write(fd_out, current->value, ft_strlen(current->value));
			write(fd_out, "\"", 1);
		}
		write(fd_out, "\n", 1);
		current = current->next;
	}
}

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

void	add_node(t_data *data, t_envp *new)
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

int	export(t_data *data, char **argv, int fd_out)
{
	t_envp	*new;
	int		ret;
	int		i;

	ret = 0;
	if (!argv[1])
		return (print_no_args(data, fd_out), 0);
	i = 1;
	while (argv[i])
	{
		new = create_new_envp_node(argv[i]);
		if (!new)
			return (1);
		if (is_valid_id(new->id) == false)
		{
			ret = 1;
			free_envp_list(new);
		}
		else
			add_node(data, new);
		i++;
	}
	return (ret);
}
