/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_create.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 17:25:45 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 17:57:06 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_id(char *str)
{
	int			equal;
	int			len;

	equal = ft_strchr_index(str, '=');
	len = ft_strlen(str);

	if (equal == -1)
		return (ft_strdup(str));
	if (str[equal - 1] == '+')
		equal -= 1;
	return (ft_substr(str, 0, equal));
}

static char	*get_env_value(char *str)
{
	int			equal;

	equal = ft_strchr_index(str, '=');
	if (equal == -1)
		return (NULL);
	return (ft_strdup(str + equal));
}

t_envp	*init_envp_node(void)
{
	t_envp	*new_node;

	new_node = (t_envp *) malloc(1 * sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->str = NULL;
	new_node->id = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_envp	*create_new_envp_node(char *str)
{
	t_envp	*new;

	new = init_envp_node();
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free_envp_list(new);
		return (NULL);
	}
	new->id = get_env_id(str);
	if (!new->id)
	{
		free_envp_list(new);
		return (NULL);
	}
	new->value = get_env_value(str);
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
