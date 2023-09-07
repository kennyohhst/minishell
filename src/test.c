/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:25:51 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/02 14:24:32 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_data(t_data *data)
{
	int		x;
	t_data	*temp;

	x = 0;
	if (!data)
		return ;
	temp = data;
	while (temp->command)
	{
		while (temp->command->argv && temp->command->argv[x])
			printf("%s\n", temp->command->argv[x++]);
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
