/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:53:30 by kkalika           #+#    #+#             */
/*   Updated: 2023/07/30 16:04:00 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_string(t_input **token)
{
	if ((*token)->token_type >= 6)
	{
		(*token) = (*token)->next;
		return (1) ;
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

int	valid_input_check(t_input *token, t_input *temp)
{
	if (temp && token->token_type == PIPE)
		return (write(1, "syntax error\n", 14), 0);
	while (temp)
	{
		if (if_string(&temp))
			continue ;
		if (temp->token_type == 1)
			return (write(1, "syntax error\n", 14), 0);
		if (temp->token_type == 0)
		{
			if (next_check(&temp))
				continue ;
			return (write(1, "syntax error\n", 14), 0);
		}
		if (temp->token_type >= 2 && temp->token_type <= 5)
		{
			temp = temp->next;
			if (temp && temp->token_type >= 6)
				continue ;
			return (write(1, "syntax error\n", 14), 0);
		}
	}
	return (1);
}
