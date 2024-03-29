/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:41:28 by code              #+#    #+#             */
/*   Updated: 2023/11/15 15:43:09 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_input	*free_tokens(t_input *list)
{
	t_input	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	return (NULL);
}

static void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redirects(t_redirect *redirect)
{
	t_redirect	*tmp;

	while (redirect)
	{
		tmp = redirect;
		redirect = redirect->next;
		free(tmp->name);
		if (tmp->heredoc_fd != -1)
			close(tmp->heredoc_fd);
		free(tmp);
	}
}

void	free_envp_list(t_envp *envp)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	tmp = envp;
	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->str);
		free(tmp->value);
		free(tmp->id);
		free(tmp);
	}
}

void	free_cmd(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_argv(tmp->argv);
		free_redirects(tmp->redirects);
		free(tmp);
	}
}
