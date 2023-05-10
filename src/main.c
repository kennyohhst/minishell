/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/10 14:01:17 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_check(t_token *cmd)
{
	t_token	*temp;

	temp = cmd;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t%d\n", temp->str, temp->type);
		temp = temp->next;
	}
}

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(void)
{
	extern int	rl_catch_signals;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
}

void	checkleaks()
{
	clear_history();					// we need to implement this in our code
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*input_list;

	atexit(checkleaks);
	(void) argc;
	(void) argv;
	while (1)
	{
		init_signals();
		input_list = parse();
		if (!input_list)
			continue ;
		if (!execute(input_list, envp))
		{
			ft_free_list(input_list);
			return (2);
		}
		// list_check(input_list);
		ft_free_list(input_list);
	}
	return (0);
}
