/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 17:26:49 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/20 18:14:59 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_check(char *raw_input)
{
	if (!raw_input)
	{
		write(1, "exit\n", 5);				// this gets printed on a newline, in bash it doesnt
		exit(0);
	}
}

t_input	*lexer(void)
{
	char		*raw_input;
	t_input		*input_list;

	input_list = NULL;
	raw_input = readline("\e[1;33mC Shell >>\033[0m ");
	exit_check(raw_input);
	if (raw_input[0] == '\0')
	{
		free(raw_input);
		return (NULL);
	}
	add_history(raw_input);
	if (check_quotes(raw_input))			// only checks for the first quote symbol you find, so ["string" 'string2] should be wrong but passes your check
		create_list(&input_list, raw_input);				// 		also why do you modulo
	free(raw_input);
	return (input_list);
}
