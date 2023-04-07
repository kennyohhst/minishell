/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:54:25 by code              #+#    #+#             */
/*   Updated: 2023/04/05 18:16:30 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_s(char **string)
{
	int	i;

	i = 0;
	if (!(*string))
		return ;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}
