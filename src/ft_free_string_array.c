/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_s.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 14:54:25 by code          #+#    #+#                 */
/*   Updated: 2023/04/25 22:29:45 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_string_array(char **strings)
{
	int	i;

	i = 0;
	if (!(*strings))
		return ;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
