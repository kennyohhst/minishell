/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_str_arr.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 21:02:56 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/10 15:28:08 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	ft_free_str_arr(char **strings)
{
	int		i;

	i = 0;
	if (!strings)
		return ;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
