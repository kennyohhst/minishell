/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:21:16 by code              #+#    #+#             */
/*   Updated: 2023/04/06 19:24:17 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_nodes(t_token **cmd, t_token *temp, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	// new->str = malloc(ft_strlen(str));
	if (!new)
		exit(write(2, "Error\n", 6));
	new->str = ft_strdup(str);
	temp = (*cmd);
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		new->next = NULL;
		(*cmd) = new;
	}
}
