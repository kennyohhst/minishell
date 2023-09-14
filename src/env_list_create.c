/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_create.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 17:25:45 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 14:55:30 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_env_id(t_envp *new, char *str)
{
	int			equal;

	equal = ft_strchr_index(str, '=');
	if (equal == 0)
		return (1);
	if (equal == -1)
	{
		new->id = ft_strdup(str);
		if (!new->id)
		{
			write(STDERR_FILENO, "minishell: Malloc fail\n", 24);
			return (-1);
		}
		return (1);
	}
	if (str[equal - 1] == '+')
		equal -= 1;
	new->id = ft_substr(str, 0, equal);
	if (!new->id)
	{
		write(STDERR_FILENO, "minishell: Malloc fail\n", 24);
		return (-1);
	}
	return (1);
}

static int	set_env_value(t_envp *new, char *str)
{
	int			equal;

	equal = ft_strchr_index(str, '=');
	if (equal == -1)
		return (1);
	new->value = ft_strdup(str + equal + 1);
	if (!new->value)
	{
		write(STDERR_FILENO, "minishell: Malloc fail\n", 24);
		return (-1);
	}
	return (1);
}

t_envp	*init_envp_node(void)
{
	t_envp	*new_node;

	new_node = (t_envp *) malloc(1 * sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->str = NULL;
	new_node->id = NULL;
	new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Create a new envp node object
 * 
 * @param str 
 * @return (t_envp *) on error return NULL
 */
t_envp	*create_new_envp_node(char *str)
{
	t_envp	*new;

	new = init_envp_node();
	if (!new)
	{
		write(STDERR_FILENO, "minishell: Malloc fail\n", 24);
		return (NULL);
	}
	new->str = ft_strdup(str);
	if (!new->str)
	{
		write(STDERR_FILENO, "minishell: Malloc fail\n", 24);
		return (free_envp_list(new));
	}
	if (set_env_id(new, str) == -1)
		return (free_envp_list(new));
	if (set_env_value(new, str) == -1)
		return (free_envp_list(new));
	return (new);
}

t_envp	*environ_to_list(char **environ)
{
	t_envp		*current;
	t_envp		*head;
	int			i;

	head = create_new_envp_node(environ[0]);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (environ[i])
	{
		current->next = create_new_envp_node(environ[i]);
		if (!current->next)
		{
			free_envp_list(head);
			return (NULL);
		}
		current->next->prev = current;
		current = current->next;
		i++;
	}
	return (head);
}
