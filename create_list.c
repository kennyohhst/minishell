/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:01:44 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/12 20:38:18 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes(char *str, int q)
{
	int	i;
	
	i = ft_strlen(str);
	while (i != q)
	{
		if (str[i] == '"')
			return (i);
		i--;
	}
	return (0);
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
	i = 0;
	x = 0;
	while (temp[i])
	{
		while (is_print(temp[i]))
		{
			if (temp[i] == '"')
				i = quotes(temp + x, i);
			if (i == 0 && x != 0)
				exit (write(2, "Error quotes\n", 14));
			i++;
		}
		ft_add_nodes(cmd, NULL, ft_substr(temp, x, (i - x)));
		x = i + 1;
		i++;
	}
}
	
// 	char	**splitstr;
// 	int		x;
	
// 	if (!str)
// 		exit(2);
// 	splitstr = ft_split(str, ' ');
// 	x = 0;
// 	if (!splitstr)
// 		exit(2);
// 	while (splitstr[x] != NULL)
// 		ft_add_nodes(cmd, NULL, splitstr[x++]);
// }
