/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 18:19:15 by code          #+#    #+#                 */
/*   Updated: 2023/04/25 22:28:45 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
