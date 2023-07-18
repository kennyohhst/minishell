/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:25:51 by kkalika           #+#    #+#             */
/*   Updated: 2023/07/17 23:30:17 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_data(t_data *data)
{
	int i = 0;
	int x = 0;
	
	if (!data)
		return ;
	while (data->command)
	{
		i = 0;
		while (data->command->argv && data->command->argv[i])
		{
			printf("argv:	%s\n", data->command->argv[i]);
			i++;
		}
		while (data->command->redirects)
		{
			if (data->command->redirects->type == PIPE)
				printf("PIPE\n");
			else if (data->command->redirects->type == OR)
				printf("OR\n");
			else if (data->command->redirects->type == INPUT_REDIRECT)
				printf("INPUT_REDIRECT	%d\n", x);
			else if (data->command->redirects->type == HERE_DOC)
				printf("HERE_DOC	%d\n", x);
			else if (data->command->redirects->type == OUTPUT_REDIRECT)
				printf("OUTPUT_REDIRECT	%d\n", x);
			else if (data->command->redirects->type == APPEND)
				printf("APPEND	%d\n", x);
			else if (data->command->redirects->type == E_VARIABLE)
				printf("E_VARIABLE\n");
			else if (data->command->redirects->type == DQ_STRING)
				printf("DQ_STRING\n");
			else if (data->command->redirects->type == DQE_STRING)
				printf("DQE_STRING\n");
			else if (data->command->redirects->type == SQ_STRING)
				printf("SQ_STRING\n");
			else if (data->command->redirects->type == STRING)
				printf("STRING\n");
			if (data->command->redirects->name != NULL)
				printf("rname:	%s\n", data->command->redirects->name);
			data->command->redirects = data->command->redirects->next;
			x++;
		}
		if (data->command->next != NULL)
		{
			data->command = data->command->next;
			continue ;
		}
		data->command = data->command->next;
	}
}

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

void	list_check(t_input *tokenized_input)
{
	t_input	*temp;

	temp = tokenized_input;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t[%.2d] => %s", temp->str, temp->token_type, g_token_id[temp->token_type]);
		if (temp->spaces)
			printf(" true\n");
		else
			printf(" false\n");
		temp = temp->next;
	}
}
