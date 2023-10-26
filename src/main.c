/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/10/06 20:41:06 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data)
{
	data->envp = NULL;
	data->command = NULL;
	data->exit_code = 0;
}

void	wait_for_children(t_data *data)
{
	t_command	*cmds;
	int			w_status;

	cmds = data->command;
	while (cmds)
	{
		if (cmds->pid == 0)
			return ;
		waitpid(cmds->pid, &w_status, 0);
		cmds = cmds->next;
	}
	if (WIFEXITED(w_status))
		data->exit_code = WEXITSTATUS(w_status);
	else
		data->exit_code = 128 + WTERMSIG(w_status);
}

void	run_shell(t_data *data)
{
	char		*input;
	t_input		*tokenized_input;

	while (true)
	{
		init_signals(MAIN);
		input = readline("minishell \% ");
		if (!input)
			break ;
		tokenized_input = lexer(input, data);
		if (!tokenized_input)
			continue ;
		data->command = parser(tokenized_input);
		if (!data->command)
			continue ;
		if (execute(data) == -1)
			data->exit_code = 1;
		wait_for_children(data);
		free_tokens(tokenized_input);
		free_cmd(data->command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void) argc;
	(void) argv;
	init_data(&data);
	data.envp = environ_to_list(envp);
	run_shell(&data);
	free_envp_list(data.envp);
	return (data.exit_code);
}
