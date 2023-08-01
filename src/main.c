/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/01 21:54:26 by opelser       ########   odam.nl         */
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

int		get_next_input(char **input)
{
	*input = readline("minishell \% ");
	if (!*input)
	{
		dprintf(STDERR_FILENO, "exit\n");
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
	rl_outstream = stderr;
	init_data(&data);
	data.envp = environ_to_list(envp);
	if (!data.envp)
		return (1);
	while (1)
	{
		init_signals();
		if (get_next_input(&input) == -1)
			break ;
		tokenized_input = lexer(input);
		if (!valid_input_check(tokenized_input))
			continue ;
		expander(tokenized_input, &data);
		data.command = parser(tokenized_input);
		if (!data.command)
			continue ;
		if (execute(&data) == -1)
			data.exit_code = 69;
		else
			set_exit_code(&data);
		ft_free_input_list(tokenized_input);
	}
	return (data.exit_code);
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
