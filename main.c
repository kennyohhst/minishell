/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/06 19:30:41 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{

	t_token	*cmd;
	
    cmd = NULL;
    while (1)
    {
        parse(&cmd);
        if (cmd)
		{
        	printf("%s\n", cmd->str);
			ft_free_list(cmd);
		}
    }
    return (0);
}

            // if (raw_input[0] == 'e' && raw_input[1] == 'x' && raw_input[2] == 'i' && raw_input[3] == 't')
            //     exit(1);