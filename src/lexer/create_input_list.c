/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:51:35 by opelser           #+#    #+#             */
/*   Updated: 2023/09/02 16:59:29 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define REDIRECT 0
#define ENV_VARIABLE 1
#define DOUBLE_QUOTE 2
#define SINGLE_QUOTE 3
#define STANDARD 4

void	add_nodes(t_input **cmd, t_input *temp, char *str, int type)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return ;
	new->str = ft_strdup(str);
	if (!new->str)
		return (free(str));
	free(str);
	new->token_type = type;
	new->argcount = 0;
	temp = *cmd;
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		new->next = NULL;
		*cmd = new;
	}
}

static int	assign_token(int mode, t_input **cmd, char *str, t_data data)
{
	(void) data;
	if (mode == REDIRECT)
		return (p_d_token(cmd, str, 0, str[0]));
	if (mode == DOUBLE_QUOTE)
		return (d_quotes_token(cmd, str, data));
	if (mode == SINGLE_QUOTE)
		return (s_quotes_token(cmd, str));
	if (mode == STANDARD)
		return (std_token(cmd, str));
	return (-1);
}

static int	check_mode(char c)
{
	if (!ft_isprint(c))
		return (-1);
	if (c == '|' || c == '>' || c == '<')
		return (REDIRECT);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	return (STANDARD);
}

void	create_input_list(t_input **cmd, char *str, t_data data)
{
	int	err_check;
	int	i;
	int	mode;

	i = 0;
	expander(data, &str, NULL, 0);
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		mode = check_mode(str[i]);
		err_check = assign_token(mode, cmd, (str + i), data);
		if (err_check == -1)
			return ;
		else
			i += err_check;
	}
}
