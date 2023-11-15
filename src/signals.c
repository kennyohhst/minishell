/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:28:59 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 15:06:28 by opelser          ###   ########.fr       */
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
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(130);
	}
}


void	init_signals(t_signals sig)
{
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
}
