/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:37:25 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 16:18:57 by opelser          ###   ########.fr       */
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
			add_envp_node(data, new);
		i++;
	}
	return (ret);
}
