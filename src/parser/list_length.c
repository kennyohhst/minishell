/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_command_argv.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 22:43:09 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 14:51:32 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_length(t_input *input)
{
	int		count;

	if (!input)
		return (0);
	count = 0;
	while (input && input->token_type > 6)
	{
		input = input->next;
		count++;
	}
	return (count);
}
