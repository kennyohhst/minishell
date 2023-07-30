/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_create.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 17:25:45 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 15:56:29 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_id(char *str, int equal, int plus)
{
	char	*tmp;
	int		len;

	if (plus > 0)
		equal -= 1;
	if (equal == -1)
		len = ft_strlen(str) + 1;
	else
		len = equal + 1;

	tmp = (char *) malloc(len * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, len);
	return (tmp);
}

static char	*get_env_value(char *str)
{
	if (!str[0])
		return (ft_strdup(""));

	return (ft_strdup(str));
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
	new_node->equal = 0;
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

	new->equal = ft_strchr_index(str, '=');
	new->plus = ft_strchr_index(str, '+');

	new->id = get_env_id(str, new->equal, new->plus);
	if (!new->id)
	{
		free_envp_list(new);
		return (NULL);
	}

	if (new->equal == -1)
		return (new);
	new->value = get_env_value(str + new->equal + 1);
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
