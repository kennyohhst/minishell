/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:49 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/08 18:27:22 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_token **cmd)
{
	char	*raw_input;
	
	raw_input = (char *)1;
    while (raw_input)
    {
        raw_input = readline("aardappelschil>> ");
		printf("raw_input:	%s\n", raw_input);
		if (!(ft_strncmp(raw_input, "exit", 5)))
			exit(0);
        if (raw_input != NULL && raw_input[0] != '\0')
        {
			add_history(raw_input);
			create_list(cmd, raw_input);
			while ((*cmd) != NULL)
			{
				printf("%s\n", (*cmd)->str);
				(*cmd) = (*cmd)->next;
			}
		}
		else if (raw_input[0] == '\0')
		{
			ft_free_list((*cmd));
			*cmd = NULL;
			free(raw_input);
			break;
		}
		free(raw_input);
		ft_free_list((*cmd));
		*cmd = NULL;
    }
    rl_redisplay();
}