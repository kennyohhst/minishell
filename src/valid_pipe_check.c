/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipe_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:41:24 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/28 16:45:17 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_pipe_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	return (ft_isalnum(str[i]));
}
