/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/08 20:14:05 by opelser       ########   odam.nl         */
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

void	handle_sig(int sig)
{
	write(1, "\n", 1);
	if (sig == 2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
	}
}

void	checkleaks()
{
	clear_history(); // we need to implement this in our code
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*cmd;
	extern int	rl_catch_signals;

	atexit(checkleaks);
	(void) argc;
	(void) argv;
	cmd = NULL;
	signal(SIGINT, handle_sig);
	rl_catch_signals = 0;
	while (1)
	{
		if (parse(&cmd, (char *) 1) == -1)
			return (1);
		if (!cmd)
			continue ;
		if (!execute(cmd, envp))
		{
			ft_free_list(cmd);
			return (3);
		}
		// list_check(cmd);
		if (cmd)
		{
			ft_free_list(cmd);
			cmd = NULL;
		}
	}
	return (0);
}
