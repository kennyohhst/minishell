/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 18:51:35 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/03 19:01:23 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	add_nodes(t_token **cmd, t_token *temp, char *str, int type)
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
	if (mode == 0)
		return (p_d_token(cmd, str, 0, str[0]));
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

static int	check_char(char c)
{
	if (!ft_isprint(c))
		return (-1);
	if (c == '|' || c == '>' || c == '<')
		return (0);
	else if (c == '$')
		return (1);
	else if (c == 34)
		return (2);
	else if (c == 39)
		return (3);
	return (4);
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
