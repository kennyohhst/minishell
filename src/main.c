/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/06/14 17:11:57 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_data(t_data *data)
{
	int i = 0;
	int x = 0;
	
	if (!data)
		return ;
	while (data->command)
	{
		i = 0;
		while (data->command->argv && data->command->argv[i])
		{
			printf("argv:	%s\n", data->command->argv[i]);
			i++;
		}
		while (data->command->redirects)
		{
			if (data->command->redirects->type == PIPE)
				printf("PIPE\n");
			else if (data->command->redirects->type == OR)
				printf("OR\n");
			else if (data->command->redirects->type == INPUT_REDIRECT)
				printf("INPUT_REDIRECT	%d\n", x);
			else if (data->command->redirects->type == HERE_DOC)
				printf("HERE_DOC	%d\n", x);
			else if (data->command->redirects->type == OUTPUT_REDIRECT)
				printf("OUTPUT_REDIRECT	%d\n", x);
			else if (data->command->redirects->type == APPEND)
				printf("APPEND	%d\n", x);
			else if (data->command->redirects->type == E_VARIABLE)
				printf("E_VARIABLE\n");
			else if (data->command->redirects->type == DQ_STRING)
				printf("DQ_STRING\n");
			else if (data->command->redirects->type == DQE_STRING)
				printf("DQE_STRING\n");
			else if (data->command->redirects->type == SQ_STRING)
				printf("SQ_STRING\n");
			else if (data->command->redirects->type == STRING)
				printf("STRING\n");
			if (data->command->redirects->name != NULL)
				printf("rname:	%s\n", data->command->redirects->name);
			data->command->redirects = data->command->redirects->next;
			x++;
		}
		if (data->command->next != NULL)
		{
			data->command = data->command->next;
			continue ;
		}
		data->command = data->command->next;
	}
}

static const char *g_token_id[] = {
	[PIPE] = "PIPE",	
	[OR] = "OR",	
	[OUTPUT_REDIRECT] = "OUTPUT_REDIR",
	[APPEND] = "APPEND",
	[INPUT_REDIRECT] = "INPUT_REDIR",
	[HERE_DOC] = "HERE_DOC",
	[E_VARIABLE] = "E_VAR",
	[DQ_STRING] = "DQ_STR",
	[DQE_STRING] = "DQ_ENV_STR",
	[SQ_STRING] = "SQ_STR",
	[STRING] = "STR"
};

void	list_check(t_input *tokenized_input)
{
	t_input	*temp;

	temp = tokenized_input;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t[%.2d] => %s", temp->str, temp->token_type, g_token_id[temp->token_type]);
		if (temp->spaces)
			printf(" true\n");
		else
			printf(" false\n");
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
		// list_check(tokenized_input);
		expander(tokenized_input, data);
		data->command = parser(tokenized_input);
		// test_data(data);
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
