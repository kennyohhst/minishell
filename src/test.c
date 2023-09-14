/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:25:51 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/14 20:43:16 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_data(t_data *data)
{
	int		p;
	int		x;
	t_data	*temp;

	p = 0;
	x = 0;
	if (!data)
		return ;
	temp = data;
	while (temp->command)
	{
		printf("%sblock %d%s\n", C_DPINK, p++ ,C_RESET);
		while (temp->command->argv && temp->command->argv[x])
			printf("argv: %s\n", temp->command->argv[x++]);
		if (temp->command->redirects)
		{
			while(temp->command->redirects)
			{
				printf("	type: %i	%s\n", temp->command->redirects->type, temp->command->redirects->name);
				temp->command->redirects = temp->command->redirects->next;
			}
		}
		temp->command = temp->command->next;
		x = 0;
	}
}

void	list_check(t_input *tokenized_input)
{
	t_input	*temp;

	temp = tokenized_input;
	while (temp)
	{
		printf("%s\t\t", temp->str);
		if (temp)
			printf(" true\n");
		else
			printf(" false\n");
		temp = temp->next;
	}
}
