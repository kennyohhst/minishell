/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:41:28 by code              #+#    #+#             */
/*   Updated: 2023/08/04 19:50:20 by kkalika          ###   ########.fr       */
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


void	free_input_output(t_redirect *output)
{
	t_redirect	*tmp;

	while (output)
	{
		tmp = output;
		output = output->next;
		free(tmp->name);
		free(tmp);
	}
}

void	free_envp(t_envp *envp)
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
		free_input_output(tmp->input);
		free_input_output(tmp->output);
		free(tmp);
	}
}