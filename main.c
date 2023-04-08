/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/08 18:22:37 by kkalika          ###   ########.fr       */
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