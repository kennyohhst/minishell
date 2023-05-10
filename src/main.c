/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/10 19:46:57 by opelser       ########   odam.nl         */
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

void	checkleaks(void)
{
	clear_history();		// we need to implement this in our code somewhere
	system("leaks -q minishell");
}

int	main(void)
{
	t_token		*input_list;
	extern char	**environ;

	// atexit(checkleaks);
	while (1)
	{
		init_signals();
		input_list = parse();
		if (!input_list)
			continue ;
		if (!execute(input_list, environ))
		{
			ft_free_list(input_list);
			return (2);
		}
		// list_check(input_list);
		ft_free_list(input_list);
	}
	return (0);
}
