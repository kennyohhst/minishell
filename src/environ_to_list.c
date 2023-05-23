/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_to_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 17:25:45 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/24 00:42:55 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_id(char *str, int equal_index)
{
	char	*tmp;
	int		len;

	if (equal_index == -1)
		len = ft_strlen(str) + 1;
	else
		len = equal_index + 1;

	tmp = (char *) malloc(len * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, len);
	return (tmp);
}

char	*get_env_value(char *str, int equal_index)
{
	char	*tmp;
	int		len;

	if (equal_index <= 0)
		return (ft_strdup(""));
	else
		len = ft_strlen(str) - equal_index + 1;

	tmp = (char *) malloc(len * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str + equal_index + 1, len);
	return (tmp);
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
	new_node->equal_index = 0;
	new_node->next = NULL;
	return (new_node);
}

t_envp	*create_new_envp_node(char *str)
{
	t_envp	*new_node;
	int		equal_index;

	new_node = init_envp_node();
	if (!new_node)
		return (NULL);

	new_node->str = ft_strdup(str);
	if (!new_node->str)
		return (free_envp_list(new_node));

	equal_index = ft_strchr_index(str, '=');
	new_node->equal_index = equal_index;

	new_node->id = get_env_id(str, equal_index);
	if (!new_node->id)
		return (free_envp_list(new_node));

	new_node->value = get_env_value(str, equal_index);
	if (!new_node->value)
		return (free_envp_list(new_node));

	return (new_node);
}

t_envp	*environ_to_list(char **environ)
{
	t_envp		*current;
	t_envp		*head;
	int			i;

	head = create_new_envp_node(environ[0]);
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
	// print_envp_list(head);
	return (head);
}
