/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:25:51 by kkalika           #+#    #+#             */
/*   Updated: 2023/08/06 18:28:18 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static const char *g_token_id[] = {
	[PIPE] = "PIPE",	
	[OR] = "OR",	
	[OUTPUT_REDIRECT] = "OUTPUT_REDIR",
	[APPEND] = "APPEND",
	[INPUT_REDIRECT] = "INPUT_REDIR",
	[HERE_DOC] = "HERE_DOC",
	[E_VARIABLE] = "E_VAR",
	[DQ_STRING] = "DQ_STR",
	[DQE_STRING] = "DQ_ENV_STR",
	[SQ_STRING] = "SQ_STR",
	[STRING] = "STR"
};

void	test_data(t_data *data)
{
	int	x = 0;
	// int	y = 0;
	if (!data)
		return ;
	while (data->command)
	{
		while (data->command->argv && data->command->argv[x])
			printf("%s\n", data->command->argv[x++]);
		data->command = data->command->next;
	}
}

void	list_check(t_input *tokenized_input)
{
	t_input	*temp;

	temp = tokenized_input;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t[%.2d] => %s", temp->str, temp->token_type, g_token_id[temp->token_type]);
		if (temp)
			printf(" true\n");
		else
			printf(" false\n");
		temp = temp->next;
	}
}