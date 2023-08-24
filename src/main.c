/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/23 00:07:25 by opelser       ########   odam.nl         */
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
	{
		// dprintf(STDERR_FILENO, "exit\n");
		return (-1);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_input			*tokenized_input;
	char			*input;
	t_data			data;

	(void) argc;
	(void) argv;
	// rl_outstream = stderr;
	init_data(&data);
	data.envp = environ_to_list(envp);
	if (!data.envp)
		return (1);
	while (1)
	{
		init_signals();



		if (get_next_input(&input) == -1)
			break ;



		tokenized_input = lexer(input, data);
		// list_check(tokenized_input);
		if (!valid_input_check(tokenized_input))
		{
			data.exit_code = 2;
			continue ;
		}

		// if (lexer(tokenized_input, raw_input) == -1)
		// {
		// 	data.exit_code = 1;
		// 	continue ;
		// }

		// expander(&data, tokenized_input);
			// tokenized_input = free_tokens(tokenized_input);
		data.command = parser(tokenized_input);
		// test_data(&data);
		if (!data.command)
			continue ;


		// if (parser(&data, tokenized_input) == -1)
		// {
		// 	data.exit_code = 1;
		// 	continue ;
		// }


		if (execute(&data) == -1)
			data.exit_code = 1;
		wait_for_children(&data);


		free_tokens(tokenized_input);
		free_cmd(data.command);
	}
	return (data.exit_code);
}
