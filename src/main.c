/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/10/05 19:25:39 by kkalika          ###   ########.fr       */
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

int	get_next_input(char **input)
{
	*input = readline("minishell \% ");
	if (!*input)
		return (-1);
	return (1);
}

void	run_shell(t_input *tokenized_input, char *input, t_data data)
{
	while (1)
	{
		init_signals();
		if (get_next_input(&input) == -1)
			break ;
		tokenized_input = lexer(input, data);
		if (!valid_input_check(tokenized_input))
		{
			data.exit_code = 2;
			continue ;
		}
		data.command = parser(tokenized_input);
		// test_data(&data);
		if (!data.command)
			continue ;
		if (execute(&data) == -1)
			data.exit_code = 1;
		wait_for_children(&data);
		free_tokens(tokenized_input);
		free_cmd(data.command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_input			*tokenized_input;
	char			*input;
	t_data			data;

	tokenized_input = NULL;
	input = NULL;
	(void) argc;
	(void) argv;
	init_data(&data);
	data.envp = environ_to_list(envp);
	run_shell(tokenized_input, input, data);
	free(input);
	return (data.exit_code);
}
