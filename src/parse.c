/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:49 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/04 20:43:27 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	raw_input_check(char *raw_input, t_token **cmd)
{
	(void) cmd;
	if (!(ft_strncmp(raw_input, "exit", 5)))
	{
		free(raw_input);
		exit(0);
	}
}

int	parse(t_token **cmd, char *raw_input)
{
	while (raw_input != NULL)
	{
		raw_input = readline("aardappelschil>> ");
		raw_input_check(raw_input, cmd);
		if (raw_input != NULL && raw_input[0] != '\0')
		{
			add_history(raw_input);
			if ((quote_count(raw_input) % 2) != 0)
				create_list(cmd, raw_input);
			free(raw_input);
			break ;
		}
		else if (raw_input[0] == '\0')
		{
			ft_free_list((*cmd));
			*cmd = NULL;
			free(raw_input);
			break ;
		}
	}
	rl_redisplay();
	if (!raw_input)
		return (-1);
	return (1);
}
