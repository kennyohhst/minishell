/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:55 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/23 16:43:25 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_d_token(t_token **cmd, char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c)
			return (ft_add_nodes(cmd, NULL, ft_substr(str, 0, 2)), 2);
		else
			return (ft_add_nodes(cmd, NULL, ft_substr(str, 0, 1)), 1);
	}
	return (-1);
}

int	e_var_token(t_token **cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == 32 || str[i] == '\0')
			return (ft_add_nodes(cmd, NULL, ft_substr(str, 0, i)), i);
	}
	return (i);
}

int	d_quotes_token(t_token **cmd, char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && i != 1)
			return (ft_add_nodes(cmd, NULL, ft_substr(str, 1, i - 1)), (i + 1));
		i++;
	}
	return (-1);
}

int	s_quotes_token(t_token **cmd, char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
			return (ft_add_nodes(cmd, NULL, ft_substr(str, 1, i - 1)), (i + 1));
		i++;
	}
	return (-1);
}

int	std_token(t_token **cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == 32 || str[i] == '\0')
			return (ft_add_nodes(cmd, NULL, ft_substr(str, 0, i)), i);
	}
	return (-1);
}
