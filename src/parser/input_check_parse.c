/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:53:30 by kkalika           #+#    #+#             */
/*   Updated: 2023/09/14 15:46:11 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_string(t_input **token)
{
	if ((*token)->token_type >= 6)
	{
		(*token)->argcount++;
		if ((*token)->next)
			(*token)->next->argcount += (*token)->argcount;
		(*token) = (*token)->next;
		return (1);
	}
	return (0);
}

int	next_check(t_input **token)
{
	if ((*token)->next)
	{
		(*token) = (*token)->next;
		return (1);
	}
	return (0);
}

int	valid_input_check(t_input *token)
{
	if (token && token->token_type == PIPE)
		return (write(2, "minishell: syntax error\n", 25), 0);
	while (token)
	{
		if (if_string(&token))
			continue ;
		if (token->token_type == 1)
			return (write(2, "minishell: syntax error\n", 25), 0);
		if (token->token_type == 0)
		{
			token->argcount = 0;
			if (next_check(&token))
				continue ;
			return (write(2, "minishell: syntax error\n", 25), 0);
		}
		if (token->token_type >= 2 && token->token_type <= 5)
		{
			token = token->next;
			if (token && token->token_type >= 6)
				continue ;
			return (write(2, "minishell: syntax error\n", 25), 0);
		}
	}
	return (1);
}
