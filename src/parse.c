/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:49 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/28 18:42:05 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_token **cmd, char *raw_input)
{
	while (raw_input)
	{
		raw_input = readline("aardappelschil>> ");
		if (!(ft_strncmp(raw_input, "exit", 5)))
			exit(0);
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
}
