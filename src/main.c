/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/07/28 15:45:08 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data)
{
	extern char		**environ;

	data->envp = environ_to_list(environ);
	data->command = NULL;
	data->exit_code = 0;
}

void	checkleaks(void)
{
	clear_history();		// we need to implement this in our code somewhere
	system("leaks -q minishell");
}

void	set_exit_code(t_data *data)
{
	t_command	*cmds;
	int			w_status;

	cmds = data->command;
	while (cmds)
	{
		waitpid(cmds->pid, &w_status, 0);
		cmds = cmds->next;
	}
	if (WIFEXITED(w_status))
		data->exit_code = WEXITSTATUS(w_status);
	else
		data->exit_code = 128 + WTERMSIG(w_status);
}

int	main(void)
{
	t_input		*tokenized_input;
	t_data		data;

	// atexit(checkleaks);
	init_data(&data);
	while (1)
	{
		init_signals();
		tokenized_input = lexer();
		// if (!valid_input_check(tokenized_input, NULL))
		// 	continue ;
		// list_check(tokenized_input);
		expander(tokenized_input, &data);
		data.command = parser(tokenized_input);
		if (!data.command)
			continue ;
		// test_data(data);
		execute(data.command, data.envp);
		set_exit_code(&data);
		// printf("\n\nexit code: %d\n", data.exit_code); // test print exit code
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
