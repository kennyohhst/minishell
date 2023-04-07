/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:19:15 by code              #+#    #+#             */
/*   Updated: 2023/04/05 19:18:10 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_token *list)
{
	t_token	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}
