/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/25 19:15:02 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_check(t_input *tokenized_input)
{
	t_input	*temp;

	temp = tokenized_input;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t%d\n", temp->str, temp->token_type);
		temp = temp->next;
	}
}

static t_data	*init_data(void)
{
	extern char		**environ;
	t_data	*data;
	
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->envp = environ_to_list(environ);
	data->command = NULL;
	data->exit_code = 0;
	return (data);
}

void	checkleaks(void)
{
	clear_history();		// we need to implement this in our code somewhere
	system("leaks -q minishell");
}

int	main(void)
{
	t_input		*tokenized_input;
	t_data		*data;

	// atexit(checkleaks);
	data = init_data();
	if (!data)
		return (1);
	while (1)
	{
		init_signals();
		tokenized_input = lexer();
	
		expander(tokenized_input);
		list_check(tokenized_input);
		data->command = parser(tokenized_input);
		if (!data->command)
			continue ;
		execute(data);
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
