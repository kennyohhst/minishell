/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:50:45 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/06 18:29:15 by kkalika          ###   ########.fr       */
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

void sigquit_handler(int sig)
{
    (void) sig;
}


void	handle_sig(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*cmd;
	char	*cmd_path;

	(void) argc;
	cmd = NULL;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, sigquit_handler);
	rl_catch_signals = 0;
	while (1)
	{
		if (parse(&cmd, (char *) 1) == -1)
			exit(0);
		cmd_path = get_command_path(cmd->str);
		if (!execute(cmd_path, argv, envp))
		{
			free(cmd_path);
			ft_free_list(cmd);
			return (1);
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
