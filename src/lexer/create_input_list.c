/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:51:35 by opelser           #+#    #+#             */
/*   Updated: 2023/11/09 19:59:28 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define REDIRECT 0
#define ENV_VARIABLE 1
#define DOUBLE_QUOTE 2
#define SINGLE_QUOTE 3
#define STANDARD 4

static void	set_var(t_input **list, int type)
{
	(*list)->token_type = type;
	(*list)->argcount = 0;
}

void	add_nodes(t_input **cmd, t_input *temp, char *str, int type)
{
	t_input	*new;

	if (!str)
		return (free(str));
	new = malloc(sizeof(t_input));
	if (!new)
		return ;
	new->str = ft_strdup(str);
	if (!new->str)
		return (free(str));
	free(str);
	set_var(&new, type);
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

static int	assign_token(int mode, t_input **token_list, \
						char *str, t_data *data)
{
	(void) data;
	if (mode == REDIRECT)
		return (p_d_token(token_list, str, 0, str[0]));
	if (mode == DOUBLE_QUOTE)
		return (d_quotes_token(token_list, str));
	if (mode == SINGLE_QUOTE)
		return (s_quotes_token(token_list, str));
	if (mode == STANDARD)
		return (std_token(token_list, str));
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

void	create_input_list(t_input **token_list, char *input, t_data *data)
{
	int		err_check;
	int		i;
	int		mode;

	i = 0;
	input = expander(data, input);
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		mode = check_mode(input[i]);
		err_check = assign_token(mode, token_list, (input + i), data);
		if (err_check == -1)
			break ;
		i += err_check;
	}
	free(input);
}
