/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:01:44 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/20 20:43:31 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes(char *str, int i)
{
	if (!str)
		return (i);
	while (str[i] && str[i] != 34 && str[i] != 39)
	{
		i++;
	}
	return (i);
}

int	is_print(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	else if (c == 32)
		return (0);
	return (0);
}

void	create_list(t_token **cmd, char *str)
{
	char *temp;
	int	i;
	int	x;

	temp = str;
	i = -1;
	x = 0;
	while (temp[x])
	{
		if (i == -1)
		{
			temp = ft_strtrim(temp, "' '\t\n\v\f\r");
			i++;			
		}
		while (temp[i] == 32 || (temp[i] >= 9 && temp[i] <= 13))
			i++;
		if (temp[i] == '\0')
			break;
		while (temp[i] && is_print(temp[i]))
		{
			if (temp[i] == 34 || temp[i] == 39)
				i = quotes(temp, i + 1);
			// if (temp[i + 1] != 34 || temp[i + 1] != 39)
			// 	return;
			i++;
		}
		ft_add_nodes(cmd, NULL, ft_substr(temp, x, (i - x)));
		x = i;
		i++;
	}
}


// void	create_list(t_token **cmd, char *str)
// {
// 	char	**splitstr;
// 	int		x;
	
// 	if (!str)
// 		exit(2);
// 	splitstr = ft_split(str, 39);
// 	x = 0;
// 	if (!splitstr)
// 		exit(2);
// 	while (splitstr[x] != NULL)
// 		ft_add_nodes(cmd, NULL, splitstr[x++]);
// }
