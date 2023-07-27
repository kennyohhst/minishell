/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 17:26:49 by kkalika       #+#    #+#                 */
/*   Updated: 2023/07/27 15:30:51 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_check(char *raw_input)
{
	if (!raw_input)
	{
		printf("\e[1A");
		printf("minishell >> exit\n");
		exit(0);
	}
}

t_input	*lexer(void)
{
	char		*raw_input;
	t_input		*input_list;

	input_list = NULL;
	// raw_input = readline(C_YELLOW""C_BOLD"︻╦╤─ "C_RESET);
	// raw_input = readline(C_YELLOW""C_BOLD"▬▬ι═══════> "C_RESET); // if in put window too small, it overwrites the message
	// raw_input = readline(C_YELLOW""C_BOLD"()==[:::::::::::::> "C_RESET);
	// raw_input = readline(C_YELLOW""C_BOLD"C Shell >> "C_RESET);
	raw_input = readline("minishell >> ");
	exit_check(raw_input);
	add_history(raw_input);
	if (check_quotes(raw_input))
		create_input_list(&input_list, raw_input);
	free(raw_input);
	return (input_list);
}
