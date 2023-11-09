/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_test_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:56:52 by code              #+#    #+#             */
/*   Updated: 2023/11/09 18:30:13 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_tester(t_input *tokens)
{
	t_input *temp;
	int		i;
	
	i = 1;
	if (!tokens)
	{
		printf("\n\n---------------------------------------------------------\n");
		printf("|		Well, at least give input  		|	\n");
		printf("|	 when you run a tokenizer tester dumbass	|\n");
		printf("---------------------------------------------------------\n\n\n");
		
		return ;
	}
	temp = tokens;

	while (temp)
	{
		if (i == 1)
		{
			printf("\ninput:-----^");
			
		}
		printf("\n\n\n--------------------------------------TOKEN %d----------------------------------\n", i);
		printf("|	string:			%s	\n", temp->str);
		printf("|	string length		%ld	\n", ft_strlen(temp->str));
		printf("|	type			%d	\n", temp->token_type);
		printf("-------------------------------------------------------------------------------\n");
		temp = temp->next;
		i++;
	}
	printf("--------------------------------------OUTPUT:----------------------------------\n\n\n");
	
}


void	data_tester(t_data *cmd)
{
	t_command	*tmp;
	t_data		*tada;
	int			i;

	tada = cmd;
	tmp = cmd->command;
	i = 0;

	printf("value		%s\n", tada->envp->value);
	while (tmp)
	{
		while (tmp->argv && tmp->argv[i])
		{
			printf("argv[%d]	%s\n", i, tmp->argv[i]);
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
}