/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 23:25:51 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/07 19:28:51 by kkalika       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static const char *g_token_id[] = {
// 	[PIPE] = "PIPE",	
// 	[OR] = "OR",	
// 	[OUTPUT_REDIRECT] = "OUTPUT_REDIR",
// 	[APPEND] = "APPEND",
// 	[INPUT_REDIRECT] = "INPUT_REDIR",
// 	[HERE_DOC] = "HERE_DOC",
// 	[E_VARIABLE] = "E_VAR",
// 	[DQ_STRING] = "DQ_STR",
// 	[DQE_STRING] = "DQ_ENV_STR",
// 	[SQ_STRING] = "SQ_STR",
// 	[STRING] = "STR"
// };

void	test_data(t_data *data)
{
	int	x = 0;
	// int	y = 0;
	if (!data)
		return ;
	t_data	*temp = data;
	while  (temp->command)
	{
		while  (temp->command->argv && temp->command->argv[x])
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