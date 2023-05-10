/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 18:51:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/10 15:27:32 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define REDIRECT 0
#define ENV_VARIABLE 1
#define DOUBLE_QUOTE 2
#define SINGLE_QUOTE 3
#define STANDARD 4

void	ft_free_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
		free(tmp);
	}
}

void	add_nodes(t_token **cmd, t_token *temp, char *str, int type)	// I need this function explained to me
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(write(2, "Error\n", 6));
	new->str = ft_strdup(str);
	new->type = type;
	temp = (*cmd);
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
		(*cmd) = new;
	}
}

static int	tokenize(char mode, t_token **cmd, char *str)
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

void	create_list(t_token **cmd, char *str)
{
	int	err_check;
	int	i;
	int	mode;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		mode = check_mode(str[i]);			// check_mode has an error check but it's not used here, also checkmode doesnt check for >> and <<
		err_check = tokenize(mode, cmd, (str + i));
		if (err_check == -1)
			return ;						// just returning doesn't tell the caller function that it's failed
		else
			i += err_check;
	}
}
