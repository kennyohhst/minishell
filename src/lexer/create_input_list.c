/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:51:35 by opelser           #+#    #+#             */
/*   Updated: 2023/08/01 21:41:47 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define REDIRECT 0
#define ENV_VARIABLE 1
#define DOUBLE_QUOTE 2
#define SINGLE_QUOTE 3
#define STANDARD 4

void	add_nodes(t_input **cmd, t_input *temp, char *str, int type)	// I need this function explained to me
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		exit(write(2, "Error\n", 6));
	new->str = ft_strdup(str);
	new->spaces = false;
	free(str);
	new->token_type = type;
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

static int	assign_token(char mode, t_input **cmd, char *str)
{
	if (mode == REDIRECT)
		return (p_d_token(cmd, str, 0, str[0]));
	if (mode == ENV_VARIABLE)
		return (e_var_token(cmd, str));
	if (mode == DOUBLE_QUOTE)
		return (d_quotes_token(cmd, str));
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
	else if (c == '$')
		return (ENV_VARIABLE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	return (STANDARD);
}
int	spaces(t_input **cmd, char *str, int i)
{
	while (str && str[i] && str[i] == ' ')
	{	
		i++;
		while ((*cmd)->next != NULL)
			(*cmd) = (*cmd)->next;
		(*cmd)->spaces = true;
	}
	return (i);
}


void	create_input_list(t_input **cmd, char *str)
{
	int	err_check;
	int	i;
	int	mode;
	t_input	*temp;

	i = 0;
	while (str[i])
	{
		i = spaces(&temp, str, i);
		mode = check_mode(str[i]);			// check_mode has an error check but it's not used here, also checkmode doesnt check for >> and <<
		err_check = assign_token(mode, cmd, (str + i));
		if (err_check == -1)
			return ;						// just returning doesn't tell the caller function that it's failed
		else
			i += err_check;
		temp = (*cmd);
	}
}
