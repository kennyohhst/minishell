/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 22:37:25 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/23 20:44:57 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_no_args(t_program_data *data)
{
	t_envp		*current;
	
	current = data->envp;
	while (current)
	{
		write(1, "declare -x", 11);
		write(1, current->id, ft_strlen(current->id));
		if (current->equal_index > 0)
		{
			write(1, "=\"", 1);
			write(1, current->value, ft_strlen(current->value));
		}
		write(1, "\"\n", 2);
		current = current->next;
	}
}

void	export(t_program_data *data)
{
	// if (!data->command->argv[1])
	print_no_args(data);
}