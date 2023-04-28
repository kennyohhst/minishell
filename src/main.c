/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/28 18:44:20 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_check(t_token *cmd)
{
	t_token	*temp;

	temp = cmd;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t%d\n", temp->str, temp->type);
		temp = temp->next;
	}
}

int	main(void)
{
	t_token	*cmd;

	cmd = NULL;
	while (1)
	{
		parse(&cmd, (char *) 1);
		list_check(cmd);
		if (cmd)
		{
			ft_free_list(cmd);
			cmd = NULL;
		}
	}
	return (0);
}
