/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:01:44 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/23 16:52:29 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char mode, t_token **cmd, char *str)
{
	if (mode == 0)
		return (p_d_token(cmd, str));
	if (mode == 1)
		return (e_var_token(cmd, str));
	if (mode == 2)
		return (d_quotes_token(cmd, str));
	if (mode == 3)
		return (s_quotes_token(cmd, str));
	if (mode == 4)
		return (std_token(cmd, str));
	return (-1);
}

int	is_print(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	else if (c == 32)
		return (0);
	return (0);
}

int	check_char(char c)
{
	if (is_print(c))
	{
		if (c == '|' || c == '>' || c == '<')
			return (0);
		else if (c == '$')
			return (1);
		else if (c == 34)
			return (2);
		else if (c == 39)
			return (3);
		else
			return (4);
	}
	return (-1);
}

void	create_list(t_token **cmd, char *str)
{
	int	err_check;
	int	i;
	int	mode;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == 32)
			i++;
		if (str[i] == '\0')
			break ;
		mode = check_char(str[i]);
		err_check = tokenize(mode, cmd, (str + i));
		if (err_check == -1)
			return ;
		else
			i += err_check;
	}
}
