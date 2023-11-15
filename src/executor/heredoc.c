/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:30:44 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 17:01:24 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	close_heredoc(t_command *command)
{
	t_redirect	*redirect;

	while (command)
	{
		redirect = command->redirects;
		while (redirect)
		{
			if (redirect->heredoc_fd != -1)
				close(redirect->heredoc_fd);
			redirect = redirect->next;
		}
		command = command->next;
	}
}

int	handle_heredoc(t_data *data)
{
	t_command	*temp;

	temp = data->command;
	while (temp)
	{
		if (find_heredoc(data, temp->redirects) == -1)
		{
			close_heredoc(data->command);
			free_cmd(data->command);
			return (-1);
		}
		temp = temp->next;
	}
	return (0);
}
