/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/07/31 23:12:07 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data)
{
	data->envp = NULL;
	data->command = NULL;
	data->exit_code = 0;
}

void	set_exit_code(t_data *data)
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

int	main(int argc, char **argv, char **envp)
{
	t_input			*tokenized_input;
	t_data			data;

	(void) argc;
	(void) argv;
	init_data(&data);
	data.envp = environ_to_list(envp);
	if (!data.envp)
		return (1);
	while (1)
	{
		init_signals();
		printf("(%d) ", data.exit_code);
		tokenized_input = lexer();
		if (!valid_input_check(tokenized_input, tokenized_input))
			continue ;
		// list_check(tokenized_input);
		expander(tokenized_input, &data);
		data.command = parser(tokenized_input);
		if (!data.command)
			continue ;
		// test_data(data);
		if (execute(&data) == -1)
			data.exit_code = 69;
		else
			set_exit_code(&data);
		ft_free_input_list(tokenized_input);
	}
	// ft_free_data(data); // free everything!!!!
	return (0);
}

/*
int main()
{
	while (1)
	{
		initialize signals
		get the tokenized list of input
		parser
		{
			expander
			{
				transform the requested environment variables to strings
				if ($?)
					get saved exit code from global or from main struct
			}
			transform the tokens into a list of commands
			make a list of redirects for every command so the executor knows where the output should go
		}
		executor
		{
			if (builtin && no redirects)
				execute in parent
			else if (builtin)
				execute in child process
			else
				execute in child process with execve
			save exit code // ernumber in main struct or in a global so we can print it
			free current command and set the command list head to next
		}
		free list
	}
	at exit: free program data and environment list
}
*/
