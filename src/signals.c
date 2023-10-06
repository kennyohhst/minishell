/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:28:59 by opelser           #+#    #+#             */
/*   Updated: 2023/10/06 19:32:54 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
}
void	init_signals(int s)
{
	extern int	rl_catch_signals;
	
	if (s == 0)
	{
		signal(SIGINT, sig_main);
		signal(SIGQUIT, SIG_IGN);
	}
	if (s == 1)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (s == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);	
	}
	if (s == 3)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);	
	}
	
	
	
	rl_catch_signals = 0;
}
