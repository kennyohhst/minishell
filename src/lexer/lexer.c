/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: code <code@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 17:26:49 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/01 15:58:46 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*lexer(char *input)
{
	t_input		*input_list;

	input_list = NULL;
	if (input[0] != '\0')
		add_history(input);
	if (check_quotes(input))
		create_input_list(&input_list, input);
	free(input);
	return (input_list);
}
