/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 14:28:59 by opelser       #+#    #+#                 */
/*   Updated: 2023/11/14 12:52:49 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sig_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit\n", 5);
	}
}

static void	sig_main(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n>", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(130);
	}
}


void	init_signals(t_signals sig)
{
	extern int	rl_catch_signals;

	if (sig == MAIN)
	{
		signal(SIGINT, sig_main);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == HEREDOC)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == CHILD)
	{
		signal(SIGINT, sig_child);
		signal(SIGQUIT, sig_child);
	}
	rl_catch_signals = 0;
}
