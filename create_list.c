/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:01:44 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/06 19:45:12 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list(t_token **cmd, char *str)
{
	char	**splitstr;
	int		x;
	
	if (!str)
		exit(2);
	splitstr = ft_split(str, ' ');
	x = 0;
	if (!splitstr)
		exit(2);
	while (splitstr[x] != NULL)
		ft_add_nodes(cmd, NULL, splitstr[x++]);
}
